#ifndef GENERATOR
#define GENERATOR

template<typename T, typename F, typename C>
class Generator {

public:
    Generator(T&& initValue, F&& genFunction, C&& genCondition);

    T current();
    bool next();
    using genType = T;

private:
    bool first_ = true;

    T current_;
    F genFunction;
    C genCondition;
};

template<typename T, typename F, typename C>
Generator<T, F, C> makeGenerator(T&& initValue, F&& genFunction, C&& genCondition);

#endif // GENERATOR

