#pragma once
#include "../../core/graphics/IColor.h"

namespace graphics {

class GradientColor : public core::graphics::IColor {
public:
  void ApplyToShape() override;
};

}