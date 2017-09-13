#ifndef GROUP
#define GROUP

#include <vector>

#include "stream_provider.h"

template<typename T>
class Group : public StreamProvider<std::vector<T>> {

public:
    Group(StreamProviderPtr<T>&& source, const size_t N);
    std::shared_ptr<std::vector<T>> current() override;
    bool next() override;

private:
    StreamProviderPtr<T> source_;
    const size_t N_;
    std::shared_ptr<std::vector<T>> current_;
};

#endif // GROUP

