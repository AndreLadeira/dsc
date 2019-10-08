TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    atsp.cpp \
        main.cpp \
    greedysdhc.cpp \
    atsp_decision.cpp

HEADERS += \
    accept_functor.h \
    atsp.h \
    atsp_decision.h \
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
    types.h \
    noncopyable.h \
    typetraits.h

CONFIG(debug, debug|release) {
    DEFINES += "__DEBUG__"
}
CONFIG(release, debug|release) {
    macx | linux: QMAKE_CXXFLAGS += -O3
}
