#ifndef ASCIIARTERMAINDIALOG_H
#define ASCIIARTERMAINDIALOG_H

#include <iosfwd>
#include <string>
#include <vector>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Weffc++"
#include <boost/shared_ptr.hpp>
#include "about.h"
#pragma GCC diagnostic pop

struct QImage;

namespace ribi {

struct ImageCanvas;
struct AsciiArter;

///AsciiArterMainDialog converts a graphics file to ASCII art
struct AsciiArterMainDialog
{
  ///Will throw an exception if
  ///- the file does not exists
  ///- the number of columns is less than five
  AsciiArterMainDialog(
    const std::string& filename,
    const int n_cols
  );

  std::vector<std::string> GetAsciiArt() const noexcept;
  const boost::shared_ptr<ImageCanvas> GetImageCanvas() const noexcept;

  private:


  ///Will throw an exception if
  ///- file does not exist
  ///- n_cols < 5
  //static const std::vector<std::string> CreateAsciiArt(
  //  const std::string& filename, const int n_cols);

  //const std::vector<std::string> m_asciiart;
  const std::string m_filename;
  const int m_n_cols;
};

std::ostream& operator<<(std::ostream& os, const AsciiArterMainDialog& d);

} //~namespace ribi

#endif // ASCIIARTERMAINDIALOG_H
