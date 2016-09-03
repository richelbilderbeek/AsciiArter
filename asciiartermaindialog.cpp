//---------------------------------------------------------------------------
/*
AsciiArter, tool to create ASCII art
Copyright (C) 2006-2016 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/ToolAsciiArter.htm
//---------------------------------------------------------------------------
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
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
#include "testtimer.h"
#include "trace.h"
#pragma GCC diagnostic pop

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

const boost::shared_ptr<ribi::ImageCanvas> ribi::AsciiArterMainDialog::GetImageCanvas() const noexcept
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
