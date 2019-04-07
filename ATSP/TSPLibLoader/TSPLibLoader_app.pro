TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "../"

SOURCES += \
    main.cpp \
    TSPLibLoader.cpp

HEADERS += \
    TSPLibLoader.h

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    LIBS += ../_libs/libatsp_based.a
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   LIBS += ../../_libs/libatsp_base.a
   QMAKE_CXXFLAGS += -O3
}
