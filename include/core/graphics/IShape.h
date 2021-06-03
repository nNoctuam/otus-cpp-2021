#pragma once

#include "../Canvas.h"
namespace core {
namespace graphics {

class IShape {
public:
  virtual void Render();

private:
  std::weak_ptr<Canvas> _canvas;
};

} // namespace graphics
} // namespace core