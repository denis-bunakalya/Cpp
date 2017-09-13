#include "generator.h"

template<typename T, typename F, typename C>
Generator<T, F, C>::Generator(T&& initValue, F&& genFunction, C&& genCondition) :

    current_(std::forward<T>(initValue)),
    genFunction(std::forward<F>(genFunction)),
    genCondition(std::forward<C>(genCondition)) {}

template<typename T, typename F, typename C>
T Generator<T, F, C>::current() {

    return current_;
}

template<typename T, typename F, typename C>
bool Generator<T, F, C>::next() {

    if(first_) {
        first_ = false;
        return genCondition(std::move(current_));
    }

    if (genCondition(current_)) {
        current_ = std::move(genFunction(std::move(current_)));
    }
    return genCondition(current_);
}

template<typename T, typename F, typename C>
Generator<T, F, C> makeGenerator(T&& initValue, F&& genFunction, C&& genCondition) {

    return Generator<T, F, C>(std::forward<T>(initValue),
                              std::forward<F>(genFunction),
                              std::forward<C>(genCondition));
}
