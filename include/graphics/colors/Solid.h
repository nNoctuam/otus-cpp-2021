#pragma once
#include "../../core/graphics/IColor.h"

namespace graphics {

class SolidColor : public core::graphics::IColor {
public:
  void ApplyToShape() override;
};

}