#ifndef STREAM_H
#define STREAM_H

#include <vector>
#include <ostream>

#include "stream_provider.h"
#include "operator.h"

template<typename T>
class Stream {

public:
    Stream(StreamProviderPtr<T> source);
    std::vector<T> to_vector();
    std::ostream&& print_to(std::ostream& os, const char* delimiter = " ");

    template<typename F>
    std::result_of_t<F(Stream<T>)> operator| (Operator<F>&& op);

    template<typename F>
    std::result_of_t<F(Stream<T>)> operator| (Operator<F>& op);

    StreamProviderPtr<T>&& extractSource();
    T getType();

    T&& getNext();
    std::shared_ptr<T> current();
    bool next();

private:
    StreamProviderPtr<T> source_;
};

#include "stream.cpp"
#include "compose.cpp"
#include "operator.cpp"
#include "iterator.cpp"
#include "container.cpp"
#include "gen_provider.cpp"
#include "generator.cpp"
#include "make_stream.cpp"
#include "stream_operators.cpp"
#include "map.cpp"
#include "filter.cpp"
#include "skip.cpp"
#include "group.cpp"

#endif // STREAM_H
