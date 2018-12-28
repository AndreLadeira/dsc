TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "../../"
INCLUDEPATH += "../../../"

LIBS += ../../_libs/libatsp_base.a
#LIBS += ../../_libs/libbase.a
LIBS += ../../_libs/libTSPLibLoader.a

SOURCES += \
        main.cpp \
    betting_algorithm.cpp

HEADERS += \
    betting_algorithm.h
