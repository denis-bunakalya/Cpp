#include "stream_operators.h"

#include "stream.h"
#include "map.h"
#include "filter.h"
#include "skip.h"
#include "group.h"

template<typename Transform>
auto map(Transform&& transform) {

    return make_operator([&](auto&& stream) {

        using T = decltype(stream.getType());
        using R = std::result_of_t<Transform(T&&)>;

        return Stream<R>(
                    StreamProviderPtr<R>(

                        new Map<R, Transform, T>(
                            stream.extractSource(),
                            std::forward<Transform>(transform))));
    });
}

template<typename IdentityFn, typename Accumulator>
auto reduce(IdentityFn&& identityFn, Accumulator&& accum) {

    return make_operator([&](auto&& stream) {

        auto result = identityFn(stream.getNext());
        while(stream.next()) {
            result = std::move(accum(std::move(result), std::move(*(stream.current()))));
        }
        return result;
    });
}

template<typename Accumulator>
auto reduce(Accumulator&& accum) {

    return reduce([] (auto x) {return x;}, std::forward<Accumulator>(accum));
}

auto sum() {

    return reduce([] (auto x, auto y) {
        return std::move(x) + std::move(y);});
}

template<typename Predicate>
auto filter(Predicate&& predicate) {

    return make_operator([&](auto&& stream) {

        using T = decltype(stream.getType());

        return Stream<T>(
                    StreamProviderPtr<T>(

                        new Filter<T, Predicate>(
                            stream.extractSource(),
                            std::forward<Predicate>(predicate))));
    });
}

auto skip(size_t amount) {

    return make_operator([=](auto&& stream) {

        using T = decltype(stream.getType());

        return Stream<T>(
                    StreamProviderPtr<T>(

                        new Skip<T>(
                            stream.extractSource(),
                            amount)));
    });
}

auto group(const size_t N) {

    return make_operator([=](auto&& stream) {

        using T = decltype(stream.getType());

        return Stream<std::vector<T>>(
                    StreamProviderPtr<std::vector<T>>(

                        new Group<T>(
                            stream.extractSource(),
                            N)));
    });
}

auto print_to(std::ostream& os, const char* delimiter) {

    return make_operator([&os, delimiter](auto&& stream) -> std::ostream&& {

        return std::move(stream.print_to(os, delimiter));
    });
}

auto to_vector() {

    return make_operator([](auto&& stream) {

        return std::move(stream.to_vector());
    });
}

auto nth(size_t index) {

    return make_operator([=](auto&& stream) {

        return std::move((stream | skip(index)).getNext());
    });
}
