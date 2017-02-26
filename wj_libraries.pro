TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tl/Allocator.cpp \
    tl/String.cpp

HEADERS += \
    config.h \
    types.h \
    tl/Allocator.h \
    tl/construct.h \
    tl/iterator.h \
    tl/memory.h \
    tl/mpl.h \
    tl/String.h \
    tl/traits.h \
    tl/Vector.h \
    tl/numeric.h \
    tl/type_traits.h \
    tl/allocator_traits.h \
    tl/utility.h
