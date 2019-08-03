#ifndef QTASCIIARTERDIALOG_H
#define QTASCIIARTERDIALOG_H


#pragma GCC diagnostic push

#include <memory>
#include "qthideandshowdialog.h"

#include "asciiartermaindialog.h"
#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
  class QtAsciiArterMainDialog;
}

struct QImage;

namespace ribi {

class QtAsciiArterMainDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtAsciiArterMainDialog(QWidget *parent = 0);
  QtAsciiArterMainDialog(const QtAsciiArterMainDialog&) = delete;
  QtAsciiArterMainDialog& operator=(const QtAsciiArterMainDialog&) = delete;
  ~QtAsciiArterMainDialog() noexcept;

  const std::string& GetFilename() const noexcept { return m_filename; }
  int GetWidth() const noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private:
  Ui::QtAsciiArterMainDialog *ui;
  std::unique_ptr<AsciiArterMainDialog> m_dialog;
  std::string m_filename;
  void OnAnyChange();

private slots:
  void on_button_load_clicked();
  void on_box_width_valueChanged(int);
};

} //~namespace ribi

#endif // QTASCIIARTERDIALOG_H
