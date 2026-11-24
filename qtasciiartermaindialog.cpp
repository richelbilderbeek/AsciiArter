


#include "qtasciiartermaindialog.h"

//
#include <boost/lexical_cast.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QScreen>
#if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
#include <QDesktopWidget>
#endif
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

  //ASCII art needs a fixed-width font: use one if Courier New is absent,
  //as is the case in a web browser
  QFont font{ui->text->font()};
  font.setStyleHint(QFont::TypeWriter);
  font.setFixedPitch(true);
  ui->text->setFont(font);

  //Put the dialog in the screen center
  #if (QT_VERSION < QT_VERSION_CHECK(6,0,0))
  const QRect screen = QApplication::desktop()->screenGeometry();
  #else
  const QRect screen = this->screen()->geometry();
  #endif
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
  #ifdef Q_OS_WASM
  //In a web browser, there is no file system to pick a file from:
  //let the browser upload the image and store it in the in-memory file system
  QFileDialog::getOpenFileContent(
    "Images (*.png *.jpg *.jpeg *.bmp *.gif)",
    [this](const QString& name, const QByteArray& content)
    {
      qInfo() << "Received file" << name << "of" << content.size() << "bytes";
      if (name.isEmpty()) return; //User cancelled
      const QString filename{"/tmp/image." + QFileInfo(name).suffix()};
      QFile file{filename};
      if (!file.open(QIODevice::WriteOnly))
      {
        qWarning() << "Cannot write" << filename;
        return;
      }
      file.write(content);
      file.close();
      LoadFile(filename.toStdString());
      qInfo() << "Loaded" << filename << ": regular file:"
        << fileio::FileIo().IsRegularFile(filename.toStdString())
        << ", lines of ASCII art:" << ui->text->blockCount();
    }
  );
  #else
  LoadFile(QFileDialog::getOpenFileName().toStdString());
  #endif
}

void ribi::QtAsciiArterMainDialog::LoadFile(const std::string& filename)
{
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
