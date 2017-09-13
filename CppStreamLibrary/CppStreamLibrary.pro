TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    compose.cpp \
    operator.cpp \
    stream_operators.cpp \
    stream.cpp \
    make_stream.cpp \
    container.cpp \
    iterator.cpp \
    map.cpp \
    generator.cpp \
    gen_provider.cpp \
    filter.cpp \
    skip.cpp \
    group.cpp




HEADERS += \
    stream.h \
    stream_provider.h \
    stream_operators.h \
    compose.h \
    operator.h \
    iterator.h \
    make_stream.h \
    map.h \
    container.h \
    filter.h \
    generator.h \
    gen_provider.h \
    skip.h \
    group.h




