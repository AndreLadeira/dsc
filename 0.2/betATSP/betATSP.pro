TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        atsp.cpp \
        main.cpp \
    greedysdhc.cpp

HEADERS += \
    atsp.h \
    createsolution.h \
    greedysdhc.h \
    neighborhood.h \
    repository.h \
    types.h \
    functor.h \
    noncopyable.h
