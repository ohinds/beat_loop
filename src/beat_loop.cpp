// Main entry for a smart tempo-matched beat loop application

#include "loop.h"

int main(int argc, char **args) {
  Loop loop;
  loop.init();
  loop.run();
  return 0;
}
