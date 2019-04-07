TEMPLATE = subdirs

SUBDIRS = \
        ../base \
        ../ATSP/atsp/atsp_base_lib.pro \
        ../ATSP/TSPLibLoader/TSPLibLoader_lib.pro \
        ../ATSP/algorithms/greedy/greedy_app.pro \

# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered
