#pragma once

#include "../Canvas.h"
namespace core {
namespace graphics {

class IColor {
public:
  virtual void ApplyToShape();

private:
  std::weak_ptr<IShape> _shape;
};

} // namespace graphics
} // namespace core