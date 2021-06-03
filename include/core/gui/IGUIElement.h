#pragma once
#include "../Observer.h"

namespace gui {
namespace core {

class IGUIElement : ::core::Observable {
  virtual ~IGUIElement();
};

} // namespace core
} // namespace gui
