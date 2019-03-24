TEMPLATE = subdirs

SUBDIRS = \
        base \
        ATSP/TSPLibLoader \
        ATSP/atsp/atsp_base.pro \
        ATSP/algorithms/greedy \
        ATSP/algorithms/betting


# build the project sequentially as listed in SUBDIRS !
CONFIG += ordered
