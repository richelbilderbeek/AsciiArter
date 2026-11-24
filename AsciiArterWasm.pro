# AsciiArter, built for the web with Qt for WebAssembly.
#
# This project file is used by .github/workflows/create_zensical_website.yaml.
# It needs these repositories next to this one:
#
#   ../DotMatrix
#   ../RibiClasses
#
# and Boost headers, passed as: qmake BOOST_INCLUDE=/path/to/boost/include
include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../RibiClasses/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../DotMatrix/DotMatrix.pri)
include(../RibiClasses/CppImageCanvas/CppImageCanvas.pri)
include(AsciiArterDesktop.pri)

SOURCES += qtmain.cpp

TARGET = AsciiArter
CONFIG += c++17 release
CONFIG -= debug_and_release
DEFINES += NDEBUG
QT += core gui widgets

!isEmpty(BOOST_INCLUDE) {
  INCLUDEPATH += $$BOOST_INCLUDE
}
