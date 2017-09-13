#include "filter.h"

template<typename T, typename Predicate>
Filter<T, Predicate>::Filter(StreamProviderPtr<T> &&source, Predicate &&predicate)

    : source_(std::move(source)),
      predicate_(std::forward<Predicate>(predicate)) {}

template<typename T, typename Predicate>
std::shared_ptr<T> Filter<T, Predicate>::current() {

    return current_;
}

template<typename T, typename Predicate>
bool Filter<T, Predicate>::next() {

    while(source_->next()) {
        current_ = source_->current();

        if(predicate_(std::move(*current_))) {
            return true;
        }
    }
    return false;
}
