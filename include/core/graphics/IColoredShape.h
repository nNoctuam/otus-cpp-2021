#pragma once

#include "../Canvas.h"
namespace graphics {
namespace core {

class IColoredShape {
public:
  virtual void Render();

private:
  std::weak_ptr<::core::Canvas> _canvas;
  std::shared_ptr<IColor> _color;
};

} // namespace core
} // namespace graphics