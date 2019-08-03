#pragma GCC diagnostic push

#include "qtasciiartermenudialog.h"

#include <QKeyEvent>

#include "qtaboutdialog.h"
#include "asciiartermenudialog.h"
#include "qtasciiartermaindialog.h"
#include "ui_qtasciiartermenudialog.h"
#pragma GCC diagnostic pop


ribi::QtAsciiArterMenuDialog::QtAsciiArterMenuDialog(QWidget *parent) :
    QtHideAndShowDialog(parent),
    ui(new Ui::QtAsciiArterMenuDialog)
{
  ui->setupUi(this);
}

ribi::QtAsciiArterMenuDialog::~QtAsciiArterMenuDialog() noexcept
{
  delete ui;
}

void ribi::QtAsciiArterMenuDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtAsciiArterMenuDialog::on_button_start_clicked()
{
  QtAsciiArterMainDialog d;
  ShowChild(&d);
}

void ribi::QtAsciiArterMenuDialog::on_button_about_clicked()
{
  About a = AsciiArterMenuDialog().GetAbout();
  a.AddLibrary("QtHideAndShowDialog version: " + QtHideAndShowDialog::GetVersion());
  QtAboutDialog d(a);
  d.setStyleSheet(this->styleSheet());
  d.setWindowIcon(this->windowIcon());
  this->hide();
  d.exec();
  this->show();
}

void ribi::QtAsciiArterMenuDialog::on_button_quit_clicked()
{
  this->close();
}
