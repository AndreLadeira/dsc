TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += "/Users/ladeira/Documents/src/boost_1_65_1/"
INCLUDEPATH += "../../../"
INCLUDEPATH += "../../"
SOURCES += \
        main.cpp \
    random_solver.cpp

HEADERS += \
    random_solver.h