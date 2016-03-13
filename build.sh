#!/bin/bash
cd ..
pwd
ls
git clone https://github.com/richelbilderbeek/RibiClasses
git clone https://github.com/richelbilderbeek/RibiLibraries
cd AsciiArter
qmake AsciiArterConsole.pro
make
qmake AsciiArterDesktop.pro
make
qmake AsciiArterWebsite.pro
make
