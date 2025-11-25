# Marvus in C++

- [About](#about)
- [Used libraries](#used-libraries)
- [Compilation](#compilation)
- [Project guide](#project-guide)
- [Donate](#donate)

## About

This project is for learning how to work with wxWidgets and database. It is an uplift for my Java Swing flat file application.

## Used libraries

*The libraries below are listed in the order they were added to the project.*

| Name | Used for | Included in this repository |
| :------: | :----------: | :---: |
| [wxWidgets](https://www.wxwidgets.org/) | GUI | ❌ |
| [SQLite](https://www.sqlite.org/) | Database | ❌ |
| [ConsoleLib](https://github.com/Riyufuchi/ConsoleLib) | Console & utils stuff | ✅ |

## Compilation

### Compiled & Tested on

| OS | Compiler |
| :------: | :----------: |
| Ubuntu | g++ 14.2.0 |
| <s>Windows 10</s> | <s>MSVC v143</s> |

### Linux

   *For debian based systems*

   ```bash
   # wxWidgets
   sudo apt install libwxgtk3.2-dev
   # SQLite
   sudo apt install libsqlite3-dev
   ```
  
### CMake
  
   ```bash
   git clone https://github.com/Riyufuchi/ConsoleArt.git
   cd ConsoleArt
   
   # On Windows
   #Fill in paths to SQLite and WxWidgets into the CMake

   cmake -B build -S .
   cmake --build build
   ```

## Project guide

- .hpp is used for single file code, that don't have coresponfing .cpp file

## Donate

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
