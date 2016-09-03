#include "asciiartermaindialog.h"

#include <boost/test/unit_test.hpp>

#include "fileio.h"
#include <QFile>

BOOST_AUTO_TEST_CASE(ribi_concept_map_is_copy_constructable)
{
  const ribi::fileio::FileIo f;

  const std::string temp_filename = f.GetTempFileName();
  assert(!f.IsRegularFile(temp_filename));
  {
    QFile qfile(":/AsciiArter/images/R.png");
    qfile.copy(temp_filename.c_str());
  }
  BOOST_CHECK(f.IsRegularFile(temp_filename) && "Resource file must exist");

  const ribi::AsciiArterMainDialog d(temp_filename,20);
  BOOST_CHECK(!d.GetAsciiArt().empty());
  std::stringstream s;
  s << d;
  BOOST_CHECK(!s.str().empty());

  f.DeleteFile(temp_filename);
  assert(!f.IsRegularFile(temp_filename));
}

