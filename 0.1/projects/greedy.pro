QMAKE_MACOSX_DEPLOYMENT_TARGET = "10.9"

TEMPLATE = subdirs

SUBDIRS = \
        ../base \
        ../ATSP/atsp/atsp_base_lib.pro \
        ../ATSP/TSPLibLoader/TSPLibLoader_lib.pro \
        ../ATSP/algorithms/greedy/greedy_app.pro \

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered
