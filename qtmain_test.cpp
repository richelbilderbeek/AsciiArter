#include <iostream>




#include <QtTest/QtTest>


#include "qtasciiartermaindialog_test.h"
#include "qtasciiartermenudialog_test.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  int error = 0;

  //These are all tests in alphabetical order
  { ribi::qtasciiartermaindialog_test t; error |= QTest::qExec(&t, argc, argv); }
  { ribi::qtasciiartermenudialog_test t; error |= QTest::qExec(&t, argc, argv); }

  if (error == 0) { std::cout << "Pass\n"; }
  if (error != 0) { std::cout << "Fail\n"; }
  return error;
}
