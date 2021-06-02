#pragma once
#include "../IGUIElement.h"
#include <vector>

namespace core {
namespace gui {

template <typename T>
class IInput : public IGUIElement, public IClickable {
public:
  virtual ~IInput();
  virtual T GetValue();
  virtual void SetValue(T);
};

} // namespace gui
} // namespace core