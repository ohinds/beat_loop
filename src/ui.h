#pragma once

#include <sstream>
#include <string>

class Ui {

 public:

  static void globalInit(bool use_curses);

  static void globalDestroy(bool use_curses);

  Ui(bool use_curses);

  ~Ui();

  void print(const std::string &str);

  char getInput();

 private:

  bool use_curses;
};

template <typename T>
Ui& operator<<(Ui &ui, const T &t) {
  std::stringstream s;
  s << t;
  ui.print(s.str());

  return ui;
}
