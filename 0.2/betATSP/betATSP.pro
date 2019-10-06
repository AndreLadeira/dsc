TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        atsp.cpp \
        main.cpp \
    greedysdhc.cpp

HEADERS += \
    atsp_decision.h \
    create_decorators.h \
    create_functor.h \
    decorators.h \
    functors.h \
    greedysdhc.h \
    neighborhood_decorators.h \
    neighborhood_functor.h \
    repository.h \
    types.h \
    noncopyable.h \
    typetraits.h
