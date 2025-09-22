# Marvus-in-Cpp

- [About](#about)
- [Used libraries](#used-libraries)
- [Testing](#testing)
- [Documentation](#documentation)
- [Compilation and libraries](#compilation-and-libraries)
	- [Linux](#linux)
	- [MaxOS](#macos)
	- [Windows](#windows)
	- [Git and Make](#git-and-make)
- [Donate](#donate)

## About

In this repository I am rewriting Marvus — originally a Java Swing application — into C++ using wxWidgets and PostgreSQL. The project includes LaTeX documentation, and everything can be built easily with a provided Makefile.

## Used libraries

*The libraries below are listed in the order they were added to the project.*

| Name | Used for | Included in this repository |
| :------: | :----------: | :---: |
| [wxWidgets](https://www.wxwidgets.org/) | GUI | 🔴 |
| [PostgreSQL](https://www.postgresql.org/) | Database | 🔴 |
| [ConsoleLib](https://github.com/Riyufuchi/ConsoleLib) | Console & utils stuff | 🟠 |

## Testing

### Compiled & Tested on

| OS | Compiler |
| :------: | :----------: |
| Ubuntu | g++ 14.2.0 |
| <s>Windows 10</s> | <s>MSVC v143</s> |

## Documentation

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
    # (Makefile runs LaTeX twice so Table of Contents and references are correct)
    make docs
   ```


## Compilation and libraries

### Linux

   *For debian based systems*

   ```bash
   # wxWidgets
   sudo apt install libwxgtk3.2-dev
   
   # PostgreSQL
   sudo apt install postgresql postgresql-contrib libpq-dev
   ```


### MacOS

   *Using Homebrew*
   
   ```bash
   # wxWidgets
   brew install wxwidgets

   # PostgreSQL
   brew install postgresql
   ```
   
### Windows

Windows is not the primary development environment for this project.  
The recommended approach is to download official `.exe` installers from the libraries' websites (e.g., wxWidgets, PostgreSQL).  

⚠️ The provided Makefile is designed for Linux/macOS. On Windows, additional setup is required. ⚠️

If you want to stick closer to the Linux workflow, you can use [MSYS2](https://www.msys2.org/) which provides a Linux-like environment, `make`, and package management on Windows.

   
### Git and Make
  
  *Makefile automatically gets ConsoleLib and compiles it before program*
  
   ```bash
   git clone --branch main --single-branch https://github.com/Riyufuchi/Marvus-in-Cpp.git 
   cd Marvus-in-Cpp
   make
   ```

## Donate

I'm a 🇨🇿 student, so a few dollars will be enough. If you are planning to use this library in a commercial application, then it would be fair if you would send more, possibly a small share of 5-10% of monthly profits.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)