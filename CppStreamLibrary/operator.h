#ifndef OPERATOR_H
#define OPERATOR_H

#include "compose.h"

template<typename F>
class Operator {

public:
    Operator(F&& op);

    template<typename S>
    std::result_of_t<F(S&&)> apply_to (S&& stream);

    template<typename G>
    Operator<Compose<G, F>> operator| (Operator<G>&& right);

    template<typename G>
    Operator<Compose<G, F>> operator| (Operator<G>& right);

    template<typename> friend class Operator;

private:
    F operator_;
};

template<typename Function>
Operator<Function> make_operator(Function&& function);

#endif // OPERATOR_H
