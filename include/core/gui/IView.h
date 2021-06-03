#pragma once

#include "../Observer.h"
#include "IGUIElement.h"

namespace gui {
namespace core {

class IView : public ::core::Observer {
public:
  virtual void Render();
  void HandleObservableUpdate() { Render(); }
};

} // namespace core
} // namespace gui
