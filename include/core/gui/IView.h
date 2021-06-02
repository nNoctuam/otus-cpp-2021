#pragma once

#include "../Observer.h"
#include "IGUIElement.h"

namespace core {
namespace gui {

class IView : public Observer {
public:
  virtual void Render();
  void HandleObservableUpdate() { Render(); }
};

} // namespace gui
} // namespace core
