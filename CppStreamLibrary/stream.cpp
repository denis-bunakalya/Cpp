#include "stream.h"

template<typename T>
Stream<T>::Stream(StreamProviderPtr<T> source)
    : source_(std::move(source)) {}

template<typename T>
std::vector<T> Stream<T>::to_vector() {

    std::vector<T> v;
    while(source_->next()) {
        v.emplace_back(std::move(*(source_->current())));
    }
    return v;
}

template<typename T>
std::ostream&& Stream<T>::print_to(std::ostream& os, const char* delimiter) {

    while(source_->next()) {
        os << std::move(*(source_->current()));
        os << delimiter;
    }
    return std::move(os);
}

template<typename T>
StreamProviderPtr<T>&& Stream<T>::extractSource() {

    return std::move(source_);
}

template<typename T>
std::shared_ptr<T> Stream<T>::current() {

    return source_->current();
}

template<typename T>
bool Stream<T>::next() {

    return source_->next();
}

template<typename T>
T&& Stream<T>::getNext() {

    source_->next();
    return std::move(*(source_->current()));
}

template<typename T>
template<typename F>
std::result_of_t<F(Stream<T>)> Stream<T>::operator| (Operator<F>&& op) {

    return op.apply_to(std::move(*this));
}

template<typename T>
template<typename F>
std::result_of_t<F(Stream<T>)> Stream<T>::operator| (Operator<F>& op) {

    return op.apply_to(std::move(*this));
}
