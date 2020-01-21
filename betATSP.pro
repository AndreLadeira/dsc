TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    atsp.cpp \
    execution_controller.cpp \
        main.cpp \
    atsp_decision.cpp \
    betatsp_decorators.cpp \
    betatsp_core.cpp

HEADERS += \
    atsp.h \
    atsp_decision.h \
    core.h \
    decorators.h \
    execution_controller.h \
    functors.h \
    betatsp_decorators.h \
    betatsp_core.h \
    stdfunctors.h \
    simulated_annealing.h \
    greedy.h

#DEFINES += "__RESULTGEN__"

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
}
CONFIG(release, debug|release) {
    macx | linux: QMAKE_CXXFLAGS += -O3
}
