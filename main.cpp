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

  size_t max_bulk_size = atoi(argv[1]);
  auto logger = std::make_shared<Logger>();
  auto controller = Controller::create(max_bulk_size, logger);

  std::string cmd;
  while (std::cin >> cmd) {
    controller->handleInput(cmd);
  }
  if (controller->at_root()) {
    controller->run();
  }

  return 0;
}
