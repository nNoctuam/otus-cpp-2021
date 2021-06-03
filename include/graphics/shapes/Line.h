#pragma once
#include "../../core/graphics/IColoredShape.h"

namespace graphics {

class Line : public core::IColoredShape {
public:
  void Render() override;
};

}