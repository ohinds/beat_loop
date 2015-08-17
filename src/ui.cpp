#include "ui.h"

#include <iostream>

#include <ncurses.h>

using std::cout;
using std::endl;
using std::string;

void Ui::globalInit(bool use_curses) {
  if (use_curses) {
    initscr();
    noecho();
    nodelay(stdscr, TRUE);
  }
}

void Ui::globalDestroy(bool use_curses) {
  if (use_curses) {
    endwin();
  }
}

Ui::Ui(bool use_curses)
  : use_curses(use_curses) {
}

Ui::~Ui() {
}

void Ui::print(const string &str) {
  if (use_curses) {
    printw(str.c_str());
    refresh();
  }
  else {
    cout << str << endl;
  }
}

char Ui::getInput() {
  if (use_curses) {
    return getch();
  }
  else {
    return -1;
  }
}
