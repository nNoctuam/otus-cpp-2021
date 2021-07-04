#pragma once

#include "vector"

#include "ICommand.h"
#include "Logger.h"

class Container : public ICommand {
public:
  explicit Container(std::shared_ptr<Logger> logger)
      : _logger(std::move(logger)) {}

  void push(std::shared_ptr<ICommand> command) { _commands.push_back(command); }

  void run() override;

protected:
  std::vector<std::shared_ptr<ICommand>> _commands;
  std::shared_ptr<Logger> _logger;
};