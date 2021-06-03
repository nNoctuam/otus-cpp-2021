#pragma once
#include "../../core/graphics/IColor.h"

namespace graphics {

class TextureColor : public core::graphics::IColor {
public:
  void ApplyToShape() override;
};

}