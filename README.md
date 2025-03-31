# KEO-manager

- [About](#about)
- [Used libraries](#used-libraries)
- [Testing](#testing)
- [Compilation](#compilation)
- [Project guide](#project-guide)
- [Donate](#donate)

## About

This project is for learning how to work with wxWidgets and database, it takes inspiration from Far Cry 4's KEO company with some liberties to give it some theme and test data.

## Used libraries

*The libraries below are listed in the order they were added to the project.*

| Name | Used for | Included in this repository |
| :------: | :----------: | :---: |
| [wxWidgets](https://www.wxwidgets.org/) | GUI | 🔴 |
| [SQLite](https://www.sqlite.org/) | Database | 🔴 |
| [ConsoleLib](https://github.com/Riyufuchi/ConsoleLib) | Console & utils stuff | 🟠 |

## Testing

### Compiled & Tested on

| OS | Compiler |
| :------: | :----------: |
| Ubuntu | g++ 14.2.0 |
| <s>Windows 10</s> | <s>MSVC v143</s> |

## Compilation

  ### Linux

   *For debian based systems*

   ```bash
   # wxWidgets
   sudo apt install libwxgtk3.2-dev
   sudo apt install libsqlite3-dev
   ```
  
  *Makefile automatically gets ConsoleLib and compiles it before program*
  
   ```bash
   git clone --branch main --single-branch https://github.com/Riyufuchi/KEO-manager.git 
   cd ConsoleArt
   make
   ```

## Project guide

- .hpp is used for single file code, that don't have coresponfing .cpp file

## Donate

I'm a 🇨🇿 student, so a few dollars will be enough. If you are planning to use this library in a commercial application, then it would be fair if you would send more, possibly a small share of 5-10% of monthly profits.

[![ko-fi](https://ko-fi.com/img/githubbutton_sm.svg)](https://ko-fi.com/P5P11WTFL)
