#ifndef SKIP
#define SKIP

#include "stream_provider.h"

template<typename T>
class Skip : public StreamProvider<T> {

public:
    Skip(StreamProviderPtr<T>&& source, size_t skip);
    std::shared_ptr<T> current() override;
    bool next() override;

private:
    StreamProviderPtr<T> source_;
    std::shared_ptr<T> current_;
    size_t skip_;
};

#endif // SKIP

