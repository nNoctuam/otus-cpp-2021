#pragma once
#include "Command.h"
#include "Container.h"
#include "Logger.h"

class Controller : public Container,
                   public std::enable_shared_from_this<Controller> {
public:

  // todo this should not be called directly to make shared_from_this work.
  //      find a way to hide it - cannot just use default constructor
  //      because of inheritance.
  explicit Controller(size_t max_bulk_size, std::shared_ptr<Logger> logger)
      : Container(std::move(logger)), _max_bulk_size(max_bulk_size) {
  }

  static std::shared_ptr<Controller> create(size_t max_bulk_size, std::shared_ptr<Logger> logger) {
    return std::make_shared<Controller>(max_bulk_size, std::move(logger));
  }

  void handleInput(std::string &cmd);

  void run() override;

  bool at_root() const { return _call_stack.empty(); }

private:
  void go_deeper();

  void go_upper();

  void reroute_logger();

  std::shared_ptr<Container> current_controller();

  size_t _max_bulk_size;
  std::vector<std::shared_ptr<Container>> _call_stack;
};
