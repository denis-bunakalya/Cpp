#ifndef CONTAINER
#define CONTAINER

#include "iterator.h"

template<typename T, typename Cont>
class Container : public StreamProvider<T> {

public:
    Container(Cont&& cont);
    std::shared_ptr<T> current() override;
    bool next() override;

private:
    Cont cont_;
    Iterator<T, typename Cont::iterator> it;
};

#endif // CONTAINER

