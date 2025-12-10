# Marvus in C++

- [About](#about)
- [Used libraries](#used-libraries)
- [Documentation](#documentation)
- [Compilation](#compilation)
- [Donate](#donate)

## About

This project is for learning how to work with wxWidgets and database. It is an uplift for [Marvus](https://github.com/Riyufuchi/Marvus) my Java Swing flat file application.

## Used libraries

*The libraries below are listed in the order they were added to the project.*

| Name | Used for | Included in this repository |
| :------: | :----------: | :---: |
| [wxWidgets](https://www.wxwidgets.org/) | GUI | ✅ (For Windows only) |
| [SQLite](https://www.sqlite.org/) | Database | ✅ |
| [ConsoleLib](https://github.com/Riyufuchi/ConsoleLib) | Console & utils stuff | ✅ |
| [Miniz](https://github.com/richgel999/miniz) | Zip file | ✅ |
| [Boost](https://www.boost.org/) | Networking and precise decimals... | ✅ |

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
| Windows 10 | MSVC 19.50.35719.0 |

### Libraries

#### wxWidgets

   ```bash
   # On Debian based systems
   sudo apt install libwxgtk3.2-dev
   
   # On Windows
   # Just extract the zip file in libs folder.
   ```

#### Boost

   Headers and linux binaries are in **libs/** folder and [Windows binaries are located here](https://github.com/Riyufuchi/Marvus-in-Cpp/releases/tag/libs).
   Just extract the needed zip files and make sure that the structure is **boost_1_89_0/boost** and **boost_1_89_0/[platform]**.
   
### CMake
  
   ```bash
   git clone https://github.com/Riyufuchi/Marvus-in-Cpp.git
   cd Marvus-in-Cpp
   # CMake
   cmake -B build -S .
   cmake --build build --config Release
   ```

## Donate

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
