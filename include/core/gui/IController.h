#pragma once

#include "memory"

namespace gui {
namespace core {

class IController {

  // use chain of responsibility to iterate views/subcontrollers recursively
  // to find one by coordinates with clickable model
  // and call handleClick on that model
  void HandleClick();

  virtual void Run();
};

} // namespace core
} // namespace gui
