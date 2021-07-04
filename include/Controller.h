#pragma once
#include "Command.h"
#include "Container.h"
#include "Logger.h"

class Controller : public Container {
public:
  explicit Controller(size_t maxBulkLength, std::shared_ptr<Logger> logger)
      : Container(std::move(logger)), _max_bulk_size(maxBulkLength) {
    _call_stack.push_back(this);
  }

  void handleInput(std::string &cmd);

  void run() override;

private:
  void go_deeper();

  void go_upper();

  void reroute_logger();

  bool at_root() const { return _call_stack.size() == 1; }

  size_t _max_bulk_size;
  std::vector<Container *> _call_stack;
};
