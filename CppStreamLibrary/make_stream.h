#ifndef MAKE_STREAM
#define MAKE_STREAM

#include "stream.h"

template<typename Iter, typename T = typename Iter::value_type>
Stream<T> MakeStream(Iter begin, Iter end);

template<typename Cont, typename Iter = typename Cont::iterator, typename T = typename Iter::value_type>
Stream<T> MakeStream(const Cont& cont);

template<typename Cont, typename Iter = typename Cont::iterator, typename T = typename Iter::value_type>
Stream<T> MakeStream(Cont&& cont);

template<typename T>
Stream<T> MakeStream(std::initializer_list<T> init);

template<typename Generator, typename T = typename std::remove_reference_t<Generator>::genType>
Stream<T> MakeStream(Generator&& generator);

template<typename T, typename... Types>
Stream<T> MakeStream(T&& arg1, Types&&... args);

#endif // MAKE_STREAM

