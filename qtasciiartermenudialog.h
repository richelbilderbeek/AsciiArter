#ifndef QTASCIIARTERMENUDIALOG_H
#define QTASCIIARTERMENUDIALOG_H

#pragma GCC diagnostic push

#include "qthideandshowdialog.h"
#pragma GCC diagnostic pop

namespace Ui {
class QtAsciiArterMenuDialog;
}

namespace ribi {

class QtAsciiArterMenuDialog : public QtHideAndShowDialog
{
  Q_OBJECT //!OCLINT

public:
  explicit QtAsciiArterMenuDialog(QWidget *parent = 0);
  QtAsciiArterMenuDialog(const QtAsciiArterMenuDialog&) = delete;
  QtAsciiArterMenuDialog& operator=(const QtAsciiArterMenuDialog&) = delete;
  ~QtAsciiArterMenuDialog() noexcept;

protected:
  void keyPressEvent(QKeyEvent *);

private slots:
  void on_button_start_clicked();
  void on_button_about_clicked();
  void on_button_quit_clicked();

private:
  Ui::QtAsciiArterMenuDialog *ui;
};

} //~namespace ribi

#endif // QTASCIIARTERMENUDIALOG_H
