#pragma GCC diagnostic push

#include <QApplication>
#include "qtasciiartermenudialog.h"
#pragma GCC diagnostic pop

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtAsciiArterMenuDialog w;
  w.show();
  return a.exec();
}
