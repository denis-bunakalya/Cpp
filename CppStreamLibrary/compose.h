#ifndef COMPOSE_H
#define COMPOSE_H

template<typename F, typename G>
class Compose {

public:
    Compose(F&& f, G&& g);

    template<typename S>
    auto operator() (S&& stream);

private:
    F f_;
    G g_;
};

#endif // COMPOSE_H
