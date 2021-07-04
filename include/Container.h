#pragma once

#include "vector"

#include "IRunnable.h"
#include "Logger.h"

class Container : public IRunnable {
public:
  explicit Container(std::shared_ptr<Logger> logger)
      : _logger(std::move(logger)) {}

  void push(std::shared_ptr<IRunnable> command);

  void run() override;

protected:
  std::vector<std::shared_ptr<IRunnable>> _commands;
  std::shared_ptr<Logger> _logger;
};