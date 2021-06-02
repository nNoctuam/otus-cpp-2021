#pragma once
#include "../IGUIElement.h"
#include <vector>

namespace core {
namespace gui {

class IContainer : public IGUIElement {
public:
  void AddElement(std::shared_ptr<IGUIElement> element);
  void HandleClick();
  virtual ~IContainer();

private:
  std::vector<std::shared_ptr<IGUIElement>> _elements;
};

} // namespace gui
} // namespace core