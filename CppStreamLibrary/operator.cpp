#include "operator.h"

template<typename F>
Operator<F>::Operator(F&& op) : operator_(std::forward<F>(op)) {}

template<typename F>
template<typename S>
std::result_of_t<F(S&&)> Operator<F>::apply_to (S&& stream) {

    return operator_(std::forward<S>(stream));
}

template<typename F>
template<typename G>
Operator<Compose<G, F>> Operator<F>::operator| (Operator<G>&& right) {

    return {{std::move(right.operator_), std::move(operator_)}};
}

template<typename F>
template<typename G>
Operator<Compose<G, F>> Operator<F>::operator| (Operator<G>& right) {

    return {{std::move(right.operator_), std::move(operator_)}};
}

template<typename Function>
Operator<Function> make_operator(Function&& function) {

    return Operator<Function>(std::forward<Function>(function));
}
