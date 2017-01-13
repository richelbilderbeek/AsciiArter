include(../RibiLibraries/DesktopApplicationNoWeffcpp.pri)

include(../DotMatrix/DotMatrix.pri)
include(../RibiClasses/CppAbout/CppAbout.pri)
include(../RibiClasses/CppCanvas/CppCanvas.pri)
include(../RibiClasses/CppFileIo/CppFileIo.pri)
include(../RibiClasses/CppHelp/CppHelp.pri)
include(../RibiClasses/CppImageCanvas/CppImageCanvas.pri)
include(../RibiClasses/CppMenuDialog/CppMenuDialog.pri)
include(../RibiClasses/CppQtAboutDialog/CppQtAboutDialog.pri)
include(../RibiClasses/CppQtHideAndShowDialog/CppQtHideAndShowDialog.pri)

include(AsciiArterDesktop.pri)
include(AsciiArterDesktopTest.pri)

SOURCES += qtmain_test.cpp

# Thanks to Qt
QMAKE_CXXFLAGS += -Wno-unused-variable

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov

# QTest
QT += testlib
