#ifndef MAP
#define MAP

#include "stream_provider.h"

template<typename T, typename Transform, typename In>
class Map : public StreamProvider<T> {

public:
    Map(StreamProviderPtr<In>&& source, Transform&& transform);
    std::shared_ptr<T> current() override;
    bool next() override;

private:
    StreamProviderPtr<In> source_;
    Transform transform_;
    std::shared_ptr<T> current_;

};

#endif // MAP

