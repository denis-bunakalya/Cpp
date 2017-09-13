#ifndef ITERATOR
#define ITERATOR

#include "stream_provider.h"

template<typename T, typename Itr>
class Iterator : public StreamProvider<T> {

public:
    Iterator(Itr begin, Itr end);
    std::shared_ptr<T> current() override;
    bool next() override;

private:
    bool first_ = true;
    Itr current_;
    Itr end_;
};

#endif // ITERATOR

