

#include "asciiartermaindialog.h"

#include <ostream>
#include <stdexcept>

#include <boost/scoped_ptr.hpp>
#include <boost/numeric/conversion/cast.hpp>

#include <QImage>
#include <QFile>

#include "canvas.h"
#include "imagecanvas.h"
#include "fileio.h"


ribi::AsciiArterMainDialog::AsciiArterMainDialog(
  const std::string& filename,
  const int n_cols)
  : m_filename(filename),
    m_n_cols(n_cols)
{

}

std::vector<std::string> ribi::AsciiArterMainDialog::GetAsciiArt() const noexcept
{
  const boost::shared_ptr<ribi::ImageCanvas> canvas { GetImageCanvas() };
  return canvas->ToStrings();
}

boost::shared_ptr<ribi::ImageCanvas>
ribi::AsciiArterMainDialog::GetImageCanvas() const
{
  if (!fileio::FileIo().IsRegularFile(m_filename))
  {
    const std::string s = "AsciiArterMainDialog: file '"+ m_filename + "' not found";
    throw std::logic_error(s.c_str());
  }
  if (m_n_cols < 5)
  {
    throw std::logic_error("AsciiArterMainDialog: n_cols < 5");
  }
  const boost::shared_ptr<ribi::ImageCanvas> canvas {
    new ImageCanvas(m_filename,m_n_cols)
  };
  assert(canvas);
  return canvas;
}

std::ostream& ribi::operator<<(std::ostream& os, const AsciiArterMainDialog& d)
{
  os << (*d.GetImageCanvas());
  return os;
}
