#include "gen_provider.h"

template<typename T, typename Gen>
GenProvider<T, Gen>::GenProvider(Gen&& gen) : gen_(std::forward<Gen>(gen)) {}

template<typename T, typename Gen>
std::shared_ptr<T> GenProvider<T, Gen>::current() {

    return std::make_shared<T>(std::move(gen_.current()));
}

template<typename T, typename Gen>
bool GenProvider<T, Gen>::next() {

    return gen_.next();
}
