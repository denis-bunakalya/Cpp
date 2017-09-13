#include "iterator.h"

template<typename T, typename Itr>
Iterator<T, Itr>::Iterator(Itr begin, Itr end)
    : current_(begin), end_(end) {}

template<typename T, typename Itr>
std::shared_ptr<T> Iterator<T, Itr>::current() {

    return std::make_shared<T>(std::move(*current_));
}

template<typename T, typename Itr>
bool Iterator<T, Itr>::next() {

    if(first_) {
        first_ = false;
        return current_ != end_;
    }
    if (current_ != end_) {
        current_++;
    }
    return current_ != end_;
}
