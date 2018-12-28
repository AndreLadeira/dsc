#TEMPLATE = app
TEMPLATE = lib
#CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

INCLUDEPATH += "../"
#LIBS += ../../_libs/libatsp_base.a

SOURCES += \
        main.cpp \
    TSPLibLoader.cpp

HEADERS += \
    TSPLibLoader.h

CONFIG(release, debug|release) {
    QMAKE_CXXFLAGS += -O3
}
