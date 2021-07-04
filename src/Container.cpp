#pragma once

void Container::run() {
  for (size_t i = 0; i < _commands.size(); i++) {
    _commands[i]->run();
    _commands[i]->~ICommand();
    if (i < _commands.size() - 1) {
      (*_logger) << ", ";
    }
  }
  _commands.clear();
}
