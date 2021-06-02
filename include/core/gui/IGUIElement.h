#pragma once
#include "../Observer.h"

namespace core {
namespace gui {

class IGUIElement : Observable {
  virtual ~IGUIElement();
};

} // namespace gui
} // namespace core
