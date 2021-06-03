#pragma once
#include "../../core/graphics/IColor.h"

namespace graphics {

class TextureColor : public core::IColor {
public:
  void ApplyToShape() override;
};

}