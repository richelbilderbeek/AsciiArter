CONFIG += c++14
QMAKE_CXX = g++-5
QMAKE_LINK = g++-5
QMAKE_CC = gcc-5
QMAKE_CXXFLAGS += -Wall -Wextra -Werror -std=c++14

# Qt
QT += core gui

# Debug and release mode
CONFIG += debug_and_release

CONFIG(release, debug|release) {
  DEFINES += NDEBUG
}

CONFIG(release, debug|debug) {

  # gcov
  QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
  LIBS += -lgcov
}

# Prevents this error:
#/usr/include/boost/math/constants/constants.hpp:277: error: unable to find numeric literal operator 'operator""Q'
#   BOOST_DEFINE_MATH_CONSTANT(half, 5.000000000000000000000000000000000000e-01, "5.00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000e-01")
#   ^
QMAKE_CXXFLAGS += -fext-numeric-literals

# Prevent Qt for failing with this error:
# qrc_[*].cpp:400:44: error: ‘qInitResources_[*]__init_variable__’ defined but not used
# [*]: the resource filename
QMAKE_CXXFLAGS += -Wno-unused-variable

include(../RibiLibraries/Boost.pri)
include(../RibiLibraries/GeneralConsole.pri)

include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../RibiClasses/CppImageCanvas/CppImageCanvas.pri)
include(../RibiClasses/CppXml/CppXml.pri)
include(AsciiArterConsole.pri)
include(AsciiArterConsoleTest.pri)

SOURCES += main_test.cpp

# Boost.Test
LIBS += -lboost_unit_test_framework
