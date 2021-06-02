#pragma once

#include <functional>
namespace core {
namespace gui {

class IClickable {
public:
  void HandleClick();
  void SetClickHandler(std::function<void()>);

private:
  std::function<void()> _clickHandler;
};

} // namespace gui
} // namespace core