TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    tsplib_reader.cpp \
    ../atsp_base/atsp_data.cpp


HEADERS += \
    tsplib_reader.h
