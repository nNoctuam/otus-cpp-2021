#pragma once
#include "../../core/graphics/IColor.h"

namespace graphics {

class GradientColor : public core::IColor {
public:
  void ApplyToShape() override;
};

}