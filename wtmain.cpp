#include <boost/signals2.hpp>
#include <boost/scoped_ptr.hpp>
#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEnvironment.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPushButton.h>

#include "wtautoconfig.h"
#include "wtasciiartermaindialog.h"

#include <QFile>

#include "fileio.h"

struct WtApplication : public Wt::WApplication
{
  WtApplication(const Wt::WEnvironment& env)
    : Wt::WApplication(env),
    m_dialog{nullptr}
  {
    this->setTitle("AsciiArter");
    this->useStyleSheet("wt.css");
    m_dialog = root()->addWidget(std::make_unique<ribi::WtAsciiArterMainDialog>());
  }
  WtApplication(const WtApplication&) = delete;
  WtApplication& operator=(const WtApplication&) = delete;
  private:
  ribi::WtAsciiArterMainDialog * m_dialog;
};

std::unique_ptr<Wt::WApplication> createApplication(
  const Wt::WEnvironment& env)
{
  return std::make_unique<WtApplication>(env);
}

int main(int argc, char **argv)
{
  if (!ribi::fileio::FileIo().IsRegularFile("RichelbilderbeekNlBackground.png"))
  {
    QFile file(":/AsciiArter/images/RichelbilderbeekNlBackground.png");
    file.copy("RichelbilderbeekNlBackground.png");
  }

  ribi::WtAutoConfig a(argc, argv, createApplication);
  ribi::WtAutoConfig::SaveDefaultStylesheet();
  return a.Run();
}

