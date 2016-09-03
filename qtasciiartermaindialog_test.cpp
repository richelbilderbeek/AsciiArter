#include "qtasciiartermaindialog_test.h"

#include <memory>
#include <QPixmap>

#include "fileio.h"
#include "qtasciiartermaindialog.h"

void ribi::qtasciiartermaindialog_test::all_tests()
{
  const ribi::fileio::FileIo f;
  const std::string tmp_filename { get_temp_filename(".png") };
  QVERIFY(!f.IsRegularFile(tmp_filename));
  //Load image from resources, save to file
  {
    QPixmap p(":/AsciiArter/images/R.png");
    QVERIFY(p.width() > 0);
    QVERIFY(p.height() > 0);
    const bool ok{p.save(tmp_filename.c_str())};
    QVERIFY(ok);
  }
  QVERIFY(f.IsRegularFile(tmp_filename));
  AsciiArterMainDialog dialog(tmp_filename,40);
  const std::vector<std::string> v {
    dialog.GetAsciiArt()
  };
  QVERIFY(!v.empty());
  f.DeleteFile(tmp_filename);
  QVERIFY(!f.IsRegularFile(tmp_filename));
}
