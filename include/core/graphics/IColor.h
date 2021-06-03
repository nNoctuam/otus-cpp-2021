#pragma once

#include "../Canvas.h"
namespace graphics {
namespace core {

class IColor {
public:
  virtual void ApplyToShape();

private:
  std::weak_ptr<IShape> _shape;
};

} // namespace core
} // namespace graphics