include(../RibiLibraries/ConsoleApplicationNoWeffcpp.pri)

include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)

include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../RibiClasses/CppImageCanvas/CppImageCanvas.pri)
include(../RibiClasses/CppXml/CppXml.pri)
include(AsciiArterConsole.pri)
include(AsciiArterConsoleTest.pri)

SOURCES += main_test.cpp

# Thanks to Qt
QMAKE_CXXFLAGS += -Wno-unused-variable

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# C++11
QMAKE_CXX = g++-5
QMAKE_LINK = g++-5
QMAKE_CC = gcc-5
QMAKE_CXXFLAGS += -std=c++11

# Boost.Test
LIBS += -lboost_unit_test_framework
