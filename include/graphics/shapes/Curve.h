#pragma once
#include "../../core/graphics/IColoredShape.h"

namespace graphics {

class Curve : public core::graphics::IColoredShape {
public:
  void Render() override;
};

}