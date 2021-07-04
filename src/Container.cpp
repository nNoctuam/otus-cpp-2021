#pragma once

void Container::run() {
  for (size_t i = 0; i < _commands.size(); i++) {
    _commands[i]->run();
    _commands[i]->~IRunnable();
    if (i < _commands.size() - 1) {
      (*_logger) << ", ";
    }
  }
  _commands.clear();
}

void Container::push(std::shared_ptr<IRunnable> command) {
  _commands.push_back(command);
}
