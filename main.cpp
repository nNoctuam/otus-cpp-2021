#include "memory"
#include "string"

#include <iostream>

#include "include/Controller.h"
#include "include/Logger.h"

#include "src/Container.cpp"
#include "src/Controller.cpp"
#include "src/Logger.cpp"

int main(int argc, char *argv[]) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << "MAX_BULK_SIZE" << std::endl;
    return 1;
  }

  size_t max_bulk_length = atoi(argv[1]);
  Controller root(max_bulk_length, std::make_shared<Logger>());

  std::string cmd;
  std::cin >> cmd;

  while (!cmd.empty()) {
    root.handleInput(cmd);
    std::cin >> cmd;
  }
  root.run();
  return 0;
}
