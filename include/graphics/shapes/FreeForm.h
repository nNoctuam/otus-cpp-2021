#pragma once
#include "../../core/graphics/IColoredShape.h"

namespace graphics {

class FreeForm : public core::graphics::IColoredShape {
public:
  void Render() override;
};

}