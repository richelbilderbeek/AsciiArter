#include <QApplication>
#include "qtasciiartermenudialog.h"
#include "qtasciiartermaindialog.h"


int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  #ifdef Q_OS_WASM
  //In a web browser, a dialog cannot wait for another dialog to close,
  //so go straight to the main dialog
  ribi::QtAsciiArterMainDialog w;
  //The web page is the window: no title bar, top-left of the canvas
  w.setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
  w.move(0, 0);
  #else
  ribi::QtAsciiArterMenuDialog w;
  #endif
  w.show();
  return a.exec();
}
