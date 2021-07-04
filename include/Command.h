#pragma once
#include "ICommand.h"
#include "Logger.h"

class Command : public ICommand {
public:
  explicit Command(std::string name, std::shared_ptr<Logger> logger)
      : _name(std::move(name)), _logger(std::move(logger)) {}
  void run() override { (*_logger) << _name; }

private:
  std::string _name;
  std::shared_ptr<Logger> _logger;
};