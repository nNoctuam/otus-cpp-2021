#pragma once

#include "memory"

namespace core {
namespace gui {

class IController{

  // use chain of responsibility to iterate views/subcontrollers recursively
  // to find one by coordinates with clickable model
  // and call handleClick on that model
  void HandleClick();

  virtual void Run();
};

} // namespace gui
} // namespace core
