# Marvus in C++

- [About](#about)
- [Used libraries](#used-libraries)
- [Documentation](#documentation)
- [Compilation](#compilation)
- [Project guide](#project-guide)
- [Donate](#donate)

## About

This project is for learning how to work with wxWidgets and database. It is an uplift for my Java Swing flat file application.

## Used libraries

*The libraries below are listed in the order they were added to the project.*

| Name | Used for | Included in this repository |
| :------: | :----------: | :---: |
| [wxWidgets](https://www.wxwidgets.org/) | GUI | ✅ (For Windows only) |
| [SQLite](https://www.sqlite.org/) | Database | ✅ |
| [ConsoleLib](https://github.com/Riyufuchi/ConsoleLib) | Console & utils stuff | ✅ |
| [Miniz](https://github.com/richgel999/miniz) | Zip file | ✅ |

## Documentation

*PDF is included in latex-doc folder but just in case here is how to compile it by yourself.*

 ```bash
    # Make sure you have LaTeX installed

    # On Debian/Ubuntu
    sudo apt install texlive-full

    # On macOS
    brew install --cask mactex

    # On Windows
    # Get the installer from https://www.tug.org/texlive/windows.html

    # Get the repository - how to is in section Git and Make
    # Build the PDF documentation
    # (CMake runs LaTeX twice so Table of Contents and references are correct)
    cd latex-doc/
    cmake ..
    cmake --build . --target docs
   ```

## Compilation

### Compiled & Tested on

| OS | Compiler |
| :------: | :----------: |
| Ubuntu | g++ 15.2.0 |
| <s>Windows 10</s> | <s>MSVC v143</s> |

### Installing WxWidgets

#### Linux

   ```bash
   sudo apt install libwxgtk3.2-dev
   ```

#### Windows

Just extract the zip file in libs folder.
  
### CMake
  
   ```bash
   git clone https://github.com/Riyufuchi/ConsoleArt.git
   cd ConsoleArt
   # CMake
   cmake -B build -S .
   cmake --build build --config Release
   ```

## Project guide

- .hpp is used for single file code, that don't have coresponfing .cpp file

## Donate

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
