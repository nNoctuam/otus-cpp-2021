#pragma once

#include <functional>
namespace gui {
namespace core {

class IClickable {
public:
  void HandleClick();
  void SetClickHandler(std::function<void()>);

private:
  std::function<void()> _clickHandler;
};

} // namespace core
} // namespace gui