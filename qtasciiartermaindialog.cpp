


#include "qtasciiartermaindialog.h"

//
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDesktopWidget>
#include <QFileDialog>
#include <QKeyEvent>
//#include <QImage>
#include <QPixmap>

#include "asciiartermaindialog.h"
#include "fileio.h"
#include "qtaboutdialog.h"
#include "ui_qtasciiartermaindialog.h"


ribi::QtAsciiArterMainDialog::QtAsciiArterMainDialog(QWidget *parent)
  : QtHideAndShowDialog(parent),
    ui(new Ui::QtAsciiArterMainDialog),
    m_dialog{std::make_unique<AsciiArterMainDialog>("",80)},
    m_filename{}
{
  ui->setupUi(this);

  //Put the dialog in the screen center
  const QRect screen = QApplication::desktop()->screenGeometry();
  this->move( screen.center() - this->rect().center() );
}

ribi::QtAsciiArterMainDialog::~QtAsciiArterMainDialog() noexcept
{
  delete ui;
}

int ribi::QtAsciiArterMainDialog::GetWidth() const noexcept
{
  return ui->box_width->value();
}

void ribi::QtAsciiArterMainDialog::OnAnyChange()
{
  if (!fileio::FileIo().IsRegularFile(GetFilename()))
  {
    m_dialog.reset(nullptr);
    return;
  }

  m_dialog.reset(new AsciiArterMainDialog(GetFilename(),GetWidth()));
  const std::vector<std::string>& v = m_dialog->GetAsciiArt();
  ui->text->clear();

  for(const std::string& s: v)
  {
    ui->text->appendPlainText(s.c_str());
  }
}

void ribi::QtAsciiArterMainDialog::on_button_load_clicked()
{
  const std::string filename = QFileDialog::getOpenFileName().toStdString();

  if (!fileio::FileIo().IsRegularFile(filename))
  {
    m_filename = "";
    return;
  }
  m_filename = filename;
  OnAnyChange();
}

void ribi::QtAsciiArterMainDialog::keyPressEvent(QKeyEvent * event)
{
  if (event->key() == Qt::Key_Escape) close();
}

void ribi::QtAsciiArterMainDialog::on_box_width_valueChanged(int)
{
  OnAnyChange();
}
