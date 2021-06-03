#pragma once

#include "../Canvas.h"
namespace core {
namespace graphics {

class IColoredShape {
public:
  virtual void Render();

private:
  std::weak_ptr<Canvas> _canvas;
  std::shared_ptr<IColor> _color;
};

} // namespace graphics
} // namespace core