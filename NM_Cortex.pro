TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

TARGET = release_binary

SOURCES +=  Cortex_mex.cpp      \
			Cortex.cpp          \
			Cortical_Column.cpp

HEADERS +=  Cortical_Column.h   \
			Data_Storage.h      \
			Random_Stream.h     \
			Stimulation.h

SOURCES -= Cortex_mex.cpp

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CXXFLAGS_RELEASE *= -O3
