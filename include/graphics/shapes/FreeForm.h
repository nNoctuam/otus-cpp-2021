#pragma once
#include "../../core/graphics/IColoredShape.h"

namespace graphics {

class FreeForm : public core::IColoredShape {
public:
  void Render() override;
};

}