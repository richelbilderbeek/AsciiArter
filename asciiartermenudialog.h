#ifndef ASCIIARTERMENUDIALOG_H
#define ASCIIARTERMENUDIALOG_H

#include <string>
#include <vector>



#include <boost/scoped_ptr.hpp>

#include "about.h"
#include "menudialog.h"


namespace ribi {

struct AsciiArter;

struct AsciiArterMenuDialog final : public MenuDialog
{
  AsciiArterMenuDialog();
  ~AsciiArterMenuDialog() noexcept {}
  int ExecuteSpecific(const std::vector<std::string>& argv) noexcept override;
  About GetAbout() const noexcept override;
  Help GetHelp() const noexcept override;
  std::string GetVersion() const noexcept override;
  std::vector<std::string> GetVersionHistory() const noexcept override;
};

} //~namespace ribi

#endif // ASCIIARTERMENUDIALOG_H
