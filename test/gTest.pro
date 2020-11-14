include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

HEADERS += \
        tst_testGameOver.h \
        tst_testPieceMovement.h \
        tst_testPieceRemoval.h \
        tst_testpieceplacement.h \
        ../src/board.h \

SOURCES += \
        main.cpp \
        ../src/board.cpp \
