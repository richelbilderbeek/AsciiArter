#pragma GCC diagnostic push


#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#include <boost/signals2.hpp>
#include <Wt/WApplication>
#include <Wt/WContainerWidget>
#include <Wt/WEnvironment>
#include <Wt/WPaintDevice>
#include <Wt/WPaintedWidget>
#include <Wt/WPainter>
#include <Wt/WPushButton>

#include "wtautoconfig.h"
#include "wtasciiartermaindialog.h"

#include <QFile>

#include "fileio.h"
#pragma GCC diagnostic pop

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog(new ribi::WtAsciiArterMainDialog)
  {
    this->setTitle("AsciiArter");
    this->useStyleSheet("wt.css");
    root()->addWidget(m_dialog);
  }
  WtApplication(const WtApplication&) = delete;
  WtApplication& operator=(const WtApplication&) = delete;
  private:
  ribi::WtAsciiArterMainDialog * const m_dialog;
};

Wt::WApplication *createApplication(
  const Wt::WEnvironment& env)
{
  return new WtApplication(env);
}

int main(int argc, char **argv)
{
  if (!ribi::fileio::FileIo().IsRegularFile("RichelbilderbeekNlBackground.png"))
  {
    QFile file(":/AsciiArter/images/RichelbilderbeekNlBackground.png");
    file.copy("RichelbilderbeekNlBackground.png");
  }

  ribi::WtAutoConfig a(argc,argv,createApplication);
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}

