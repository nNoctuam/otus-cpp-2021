#pragma once
#include "graphics/IShape.h"

namespace core {

class Document {
public:
private:
  std::vector<std::shared_ptr<graphics::core::IShape>> _shapes;
  std::shared_ptr<Canvas> _canvas;
};

} // namespace core