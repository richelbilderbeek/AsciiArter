#pragma GCC diagnostic push

#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include "asciiartermenudialog.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

#include <boost/lexical_cast.hpp>

#include <QFile>

//#include "asciiarter.h"
#include "asciiartermaindialog.h"
#include "fileio.h"
#include "imagecanvas.h"
#pragma GCC diagnostic pop

ribi::AsciiArterMenuDialog::AsciiArterMenuDialog()
{

}

int ribi::AsciiArterMenuDialog::ExecuteSpecific(const std::vector<std::string>& argv) noexcept
{
  const int argc = static_cast<int>(argv.size());
  if (argc == 1 || argc > 4)
  {
    std::cout << GetHelp() << '\n';
    return 1;
  }
  {
    if (!fileio::FileIo().IsRegularFile(argv[1]))
    {
      std::cout
        << "Error: '" << argv[1] << "' is not found.\n"
        << "Please supply an existing file as AsciiArter its first argument\n";
      return 1;
    }
  }
  if (argc == 4)
  {
    try
    {
      const int n_cols = boost::lexical_cast<int>(argv[3]);
      if (n_cols < 5)
      {
        std::cout
          << "Error: the number of columns must be at least 5.\n"
          << "Please supply a number above 5 as AsciiArter its third argument\n";
        return 1;
      }
    }
    catch (boost::bad_lexical_cast&)
    {
      std::cout
        << "Error: '" << argv[3] << "' is not an integer number.\n"
        << "Please supply a number as AsciiArter its third argument\n";
      return 1;

    }
  }

  const std::string from_name { argv[1] };
  std::string to_name { argv[2] };
  const int n_cols{argc == 4 ? boost::lexical_cast<int>(argv[3]) : 78};

  AsciiArterMainDialog d(from_name,n_cols);
  const std::vector<std::string> v { d.GetAsciiArt() };
  std::ofstream f(to_name.c_str());
  std::copy(v.begin(),v.end(),std::ostream_iterator<std::string>(f,"\n"));
  return 0;
}

ribi::About ribi::AsciiArterMenuDialog::GetAbout() const noexcept
{
  About a(
    "Richel Bilderbeek",
    "AsciiArter",
    "tool to create ASCII art",
    "January 9th 2016",
    "2006-2017",
    "http://www.richelbilderbeek.nl/ToolAsciiArter.htm",
    GetVersion(),
    GetVersionHistory()
  );
  a.AddLibrary("ImageCanvas version: " + ImageCanvas::GetVersion());
  return a;
}

std::string ribi::AsciiArterMenuDialog::GetVersion() const noexcept
{
  return "7.0";
}

std::vector<std::string> ribi::AsciiArterMenuDialog::GetVersionHistory() const noexcept
{
  return {
    "2006-12-13: Version 1.0: initial C++ Builder version, called 'AsciiArter'",
    "2006-12-16: Version 2.0: renamed 'AsciiArter' to 'TestAsciiArter', minor improvements",
    "2008-06-21: Version 3.0: minor improvements",
    "2011-03-23: Version 4.0: port to Qt4",
    "2011-03-27: Version 4.1: added web application version",
    "2011-04-04: Version 4.2: fix bug under the web application its Convert button",
    "2011-04-25: Version 4.3: removed website version\'s Close button, "
      "use of Wt::WMenu in website version",
    "2011-08-31: Version 4.4: added Welcome picture to website version",
    "2012-07-30: Version 5.0: renamed 'TestAsciiArter' to 'AsciiArter', "
      "added menu to desktop version",
    "2012-12-24: Version 5.1: slickened desktop application looks",
    "2013-07-12: Version 5.2: transitioned to Qt5 and Boost 1.54.0",
    "2013-07-12: Version 6.0: replaced use of AsciiArter class by ImageCanvas",
    "2016-01-09: Version 7.0: moved to own GitHub",
  };
}

ribi::Help ribi::AsciiArterMenuDialog::GetHelp() const noexcept
{
  return ribi::Help(
    "AsciiArter",
    "Tool to create ASCII art images from images",
    {
      //No additional options
    },
    {
      "AsciiArter [option]\n",
      "AsciiArter --about",
      "",
      "AsciiArter [picture input filename] [text output filename] [columns = 78]\n",
      "AsciiArter source.png target.txt",
      "AsciiArter source.png target.txt 254"
    }
  );
}
