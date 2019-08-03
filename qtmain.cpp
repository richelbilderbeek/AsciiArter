

#include <QApplication>
#include "qtasciiartermenudialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  ribi::QtAsciiArterMenuDialog w;
  w.show();
  return a.exec();
}
