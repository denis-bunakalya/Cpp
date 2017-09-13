#include "skip.h"

template<typename T>
Skip<T>::Skip(StreamProviderPtr<T>&& source, size_t skip)

    : source_(std::move(source)),
      skip_(skip) {}

template<typename T>
std::shared_ptr<T> Skip<T>::current() {

    return current_;
}

template<typename T>
bool Skip<T>::next() {

    while (skip_ != 0) {
        if(!source_->next()) {
            return false;
        }
        skip_--;
    }
    if(source_->next()) {
        current_ = std::make_shared<T>(std::move(*source_->current()));
        return true;
    }
    return false;
}
