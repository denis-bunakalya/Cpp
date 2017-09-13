#include "container.h"

template<typename T, typename Cont>
Container<T, Cont>::Container(Cont&& cont)

    : cont_(std::forward<Cont>(cont)),
      it(cont_.begin(), cont_.end()) {}

template<typename T, typename Cont>
std::shared_ptr<T> Container<T, Cont>::current() {

    return it.current();
}

template<typename T, typename Cont>
bool Container<T, Cont>::next() {

    return it.next();
}
