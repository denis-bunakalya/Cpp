#ifndef STREAM_OPERATORS
#define STREAM_OPERATORS

template<typename Transform>
auto map(Transform&& transform);

template<typename IdentityFn, typename Accumulator>
auto reduce(IdentityFn&& identityFn, Accumulator&& accum);

template<typename Accumulator>
auto reduce(Accumulator&& accum);

auto sum();

template<typename Predicate>
auto filter(Predicate&& predicate);

auto skip(size_t amount);

auto group(const size_t N);

auto print_to(std::ostream& os, const char* delimiter = " ");

auto to_vector();

auto nth(size_t index);

#endif // STREAM_OPERATORS

