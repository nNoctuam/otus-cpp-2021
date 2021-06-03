#pragma once
#include "../../core/graphics/IColoredShape.h"

namespace graphics {

class Curve : public core::IColoredShape {
public:
  void Render() override;
};

}