TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    ../atsp_base/data.cpp \
    TSPLibLoader.cpp

HEADERS += \
    TSPLibLoader.h

#debug levels
CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
    QMAKE_CXXFLAGS += -O3
}
