#ifndef STREAMPROVIDER
#define STREAMPROVIDER

#include <memory>

template<typename T>
class StreamProvider {

public:
    virtual std::shared_ptr<T> current() = 0;
    virtual bool next() = 0;
};

template<typename T>
using StreamProviderPtr = std::unique_ptr<StreamProvider<T>>;

#endif // STREAMPROVIDER

