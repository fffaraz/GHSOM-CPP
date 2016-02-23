#-------------------------------------------------
#
# Project created by QtCreator 2015-12-05T21:17:40
#
#-------------------------------------------------

QT += core gui widgets

TARGET = ghsom
TEMPLATE = app
CONFIG += c++11

CONFIG  += release
DEFINES += QT_NO_DEBUG_OUTPUT

# remove possible other optimization flags
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_LFLAGS_RELEASE   -= -O
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_LFLAGS_RELEASE   -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_LFLAGS_RELEASE   -= -O2

# add the desired -O3 if not present
QMAKE_CXXFLAGS_RELEASE *= -O3
QMAKE_LFLAGS_RELEASE   *= -O3

#QMAKE_CXXFLAGS_RELEASE += -O2
#QMAKE_LFLAGS_RELEASE   += -O2

gcc:QMAKE_CXXFLAGS_RELEASE += -ffast-math
msvc:QMAKE_CXXFLAGS_RELEASE += /fp:fast

gcc:QMAKE_CXXFLAGS_RELEASE += -O3 -march=native # -fopenmp -D_GLIBCXX_PARALLEL
msvc:QMAKE_CXXFLAGS_RELEASE += /O2 /arch:AVX # /openmp 

SOURCES += main.cpp \
    neuron.cpp \
    map.cpp \
    vector.cpp \
    map_etc.cpp \
    map_find.cpp \
    gui.cpp

HEADERS += \
    neuron.h \
    map.h \
    common.h \
    vector.h \
    gui.h \
    tests.h
