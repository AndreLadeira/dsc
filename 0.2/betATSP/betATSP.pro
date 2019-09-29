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
    greedysdhc.h \
    types.h
