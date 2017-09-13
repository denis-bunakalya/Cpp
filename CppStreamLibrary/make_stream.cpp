#include "make_stream.h"
#include "container.h"
#include "gen_provider.h"

template<typename Iter, typename T = typename Iter::value_type>
Stream<T> MakeStream(Iter begin, Iter end) {

    return StreamProviderPtr<T>(new Iterator<T, Iter>(begin, end));
}

template<typename Cont, typename Iter = typename Cont::iterator, typename T = typename Iter::value_type>
Stream<T> MakeStream(const Cont& cont) {

    return MakeStream(cont.begin(), cont.end());
}

template<typename Cont, typename Iter = typename Cont::iterator, typename T = typename Iter::value_type>
Stream<T> MakeStream(Cont&& cont) {

    return StreamProviderPtr<T>(new Container<T, Cont>(std::forward<Cont>(cont)));
}

template<typename T>
Stream<T> MakeStream(std::initializer_list<T> init) {

    return MakeStream(std::move(std::vector<T>(init)));
}

template<typename Generator, typename T = typename std::remove_reference_t<Generator>::genType>
Stream<T> MakeStream(Generator&& generator) {

    return StreamProviderPtr<T>(new GenProvider<T, Generator>(std::forward<Generator>(generator)));
}

template<typename T, typename... Types>
Stream<T> MakeStream(T&& arg1, Types&&... args) {

    return MakeStream(std::move(std::vector<T> {std::forward<T>(arg1), std::forward<Types>(args)...}));
}
