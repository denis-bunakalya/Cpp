#include "group.h"

template<typename T>
Group<T>::Group(StreamProviderPtr<T>&& source, const size_t N)

    : source_(std::move(source)),
      N_(N) {}

template<typename T>
std::shared_ptr<std::vector<T>> Group<T>::current() {

    return current_;
}

template<typename T>
bool Group<T>::next() {

    std::vector<T> v;
    for (size_t i = 0; i < N_; i++) {

        if (!source_->next()) {
            return false;
        }
        v.emplace_back(std::move(*(source_->current())));
    }
    current_ = std::make_shared<std::vector<T>>(std::move(v));
    return true;
}

