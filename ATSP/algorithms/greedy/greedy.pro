TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "../../"
INCLUDEPATH += "../../../"

SOURCES += \
        main.cpp \
    greedy_algorithm.cpp

HEADERS += \
    greedy_algorithm.h

LIBS += ../../_libs/libatsp_base.a
LIBS += ../../_libs/libbase.a
LIBS += ../../_libs/libTSPLibLoader.a

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   QMAKE_CXXFLAGS += -O3
}


