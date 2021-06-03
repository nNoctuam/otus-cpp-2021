#pragma once
#include "../../core/graphics/IColor.h"

namespace graphics {

class SolidColor : public core::IColor {
public:
  void ApplyToShape() override;
};

}