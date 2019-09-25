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

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    LIBS += ../../_libs/libatsp_based.a
    LIBS += ../../_libs/libbased.a
    LIBS += ../../_libs/libTSPLibLoaderd.a
}
CONFIG(release, debug|release) {
   DEFINES += "__RELEASE__"
   QMAKE_CXXFLAGS += -O3
   LIBS += ../../_libs/libatsp_base.a
   LIBS += ../../_libs/libbase.a
   LIBS += ../../_libs/libTSPLibLoader.a
}

TARGET =  "greedyATSP.app"


