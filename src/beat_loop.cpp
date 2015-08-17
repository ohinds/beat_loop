// Main entry for a smart tempo-matched beat loop application

#include <chrono>
#include <iostream>
#include <string>
#include <thread>

#include "loop.h"
#include "ui.h"

using std::chrono::milliseconds;
using std::endl;
using std::string;
using std::this_thread::sleep_for;

bool beat_loop() {
  Ui::globalInit(true);

  Ui ui(true);
  Loop loop;
  loop.init();
  loop.run();

  char in = 0;
  while (in != 'q') {
    in = ui.getInput();
    switch(in) {
      case 'q':
        break;
      case ' ':
        loop.toggle_record();
        ui << "toggled record\n";
        break;
    }

    sleep_for(milliseconds(1));
  }

  Ui::globalDestroy(true);

  return true;
}


int main(int argc, char **args) {
  beat_loop();
  return 0;
}
