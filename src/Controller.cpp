#pragma once

#include "chrono"

void Controller::handleInput(std::string &cmd) {
  if (cmd == "{") {
    go_deeper();
  } else if (cmd == "}") {
    go_upper();
  } else if ((cmd.empty() || cmd == "EOF") && at_root()) {
    run();
  } else {
    if (at_root() && _commands.empty()) {
      reroute_logger();
    }
    _call_stack.at(_call_stack.size() - 1)->push(new Command(cmd, _logger));
    if (at_root() && _commands.size() >= _max_bulk_size) {
      run();
    }
  }
}
void Controller::run() {
  if (_commands.empty()) {
    return;
  }
  (*_logger) << "bulk: ";
  Container::run();
  (*_logger) << std::endl;
}
void Controller::go_deeper() {
  if (at_root()) {
    run();
  }

  auto cmd = new Container(_logger);
  _call_stack.at(_call_stack.size() - 1)->_commands.push_back(cmd);
  _call_stack.push_back(cmd);
}
void Controller::go_upper() {
  if (!at_root()) {
    _call_stack.pop_back();
  }
  if (at_root()) {
    run();
  }
}

void Controller::reroute_logger() {
  const auto p1 = std::time(nullptr);
  _logger->set_file_name("bulk" + std::to_string(p1) + ".log");
}
