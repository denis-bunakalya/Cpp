#ifndef GEN_PROVIDER
#define GEN_PROVIDER

#include "stream_provider.h"

template<typename T, typename Gen>
class GenProvider : public StreamProvider<T> {

public:
    GenProvider(Gen&& gen);
    std::shared_ptr<T> current() override;
    bool next() override;

private:
    Gen gen_;
};

#endif // GEN_PROVIDER

