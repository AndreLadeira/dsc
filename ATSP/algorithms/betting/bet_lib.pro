TEMPLATE = lib
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += staticlib

INCLUDEPATH += "../../"
INCLUDEPATH += "../../../"
INCLUDEPATH += "../"

SOURCES += \
    betting_phase1.cpp \
    player.cpp

HEADERS += \
    betting_phase1.h \
    player.h

DESTDIR = "../../_libs/"

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
    #LIBS += ../../_libs/libatsp_based.a
    #LIBS += ../../_libs/libbased.a
    #LIBS += ../../_libs/libGreedyAlgod.a
    TARGET =  "BetAlgod"
}
CONFIG(release, debug|release) {
    DEFINES += "__RELEASE__"
    #LIBS += ../../_libs/libatsp_base.a
    #LIBS += ../../_libs/libbase.a
    #LIBS += ../../_libs/libGreedyAlgo.a
    QMAKE_CXXFLAGS += -O3
    TARGET =  "BetAlgo"
}


