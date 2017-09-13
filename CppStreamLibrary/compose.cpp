#include "compose.h"

template<typename F, typename G>
Compose<F, G>::Compose(F&& f, G&& g) : f_(std::forward<F>(f)), g_(std::forward<G>(g)) {}

template<typename F, typename G>
template<typename S>
auto Compose<F, G>::operator() (S&& stream) {

    return f_(g_(std::forward<S>(stream)));
}
