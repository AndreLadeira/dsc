TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    atsp.cpp \
    execution_controller.cpp \
        main.cpp \
    greedysdhc.cpp \
    atsp_decision.cpp \
    betatsp_decorators.cpp \
    betatsp_core.cpp

HEADERS += \
    accept_decorator.h \
    accept_functor.h \
    atsp.h \
    atsp_decision.h \
    core.h \
    create_decorators.h \
    create_functor.h \
    decorators.h \
    execution_controller.h \
    functors.h \
    greedysdhc.h \
    neighborhood_decorators.h \
    neighborhood_functor.h \
    objective_decorators.h \
    objective_functor.h \
    repository.h \
    noncopyable.h \
    typetraits.h \
    betatsp_decorators.h \
    betatsp_core.h

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
}
CONFIG(release, debug|release) {
    macx | linux: QMAKE_CXXFLAGS += -O3
}
