#ifndef FILTER
#define FILTER

#include "stream_provider.h"

template<typename T, typename Predicate>
class Filter : public StreamProvider<T> {

public:
    Filter(StreamProviderPtr<T>&& source, Predicate&& predicate);
    std::shared_ptr<T> current() override;
    bool next() override;

private:
    StreamProviderPtr<T> source_;
    Predicate predicate_;
    std::shared_ptr<T> current_;
};

#endif // FILTER

