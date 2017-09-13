#include "map.h"

template<typename T, typename Transform, typename In>
Map<T, Transform, In>::Map(StreamProviderPtr<In>&& source, Transform&& transform)

    : source_(std::move(source)),
      transform_(std::forward<Transform>(transform)) {}

template<typename T, typename Transform, typename In>
std::shared_ptr<T> Map<T, Transform, In>::current() {

    return current_;
}

template<typename T, typename Transform, typename In>
bool Map<T, Transform, In>::next() {

    if(source_->next()) {
        current_ = std::make_shared<T>(std::move(transform_(std::move(*(source_->current())))));
        return true;
    }
    return false;
}
