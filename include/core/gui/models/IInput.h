#pragma once
#include "../IGUIElement.h"
#include <vector>

namespace gui {
namespace core {

template <typename T> class IInput : public IGUIElement, public IClickable {
public:
  virtual ~IInput();
  virtual T GetValue();
  virtual void SetValue(T);
};

} // namespace core
} // namespace gui