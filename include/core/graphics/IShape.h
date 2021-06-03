#pragma once

#include "../Canvas.h"
namespace graphics {
namespace core {

class IShape {
public:
  virtual void Render();

private:
  std::weak_ptr<::core::Canvas> _canvas;
};

} // namespace core
} // namespace graphics