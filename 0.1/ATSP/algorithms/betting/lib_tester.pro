TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "../../"
INCLUDEPATH += "../../../"
INCLUDEPATH += "../../../../"
INCLUDEPATH += "../"

SOURCES += main_lib.cpp \
    betting_phase1.cpp \
    player.cpp \
    playerstats.cpp \

HEADERS += \
    betting_phase1.h \
    player.h \
    playerstats.h

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    LIBS += ../../_libs/libatsp_based.a
    LIBS += ../../_libs/libbased.a
    LIBS += ../../_libs/libGreedyAlgod.a
    LIBS += ../../_libs/libTSPLibLoaderd.a
}
CONFIG(release, debug|release) {
    DEFINES += "__RELEASE__"
    LIBS += ../../_libs/libatsp_base.a
    LIBS += ../../_libs/libbase.a
    LIBS += ../../_libs/libGreedyAlgo.a
    QMAKE_CXXFLAGS += -O3
}