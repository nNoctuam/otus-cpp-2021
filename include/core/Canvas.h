#pragma once
#include "gui/IGUIElement.h"

namespace core {

class Canvas : gui::core::IGUIElement {
public:
  void DrawLine();
  void DrawCurve();
  void FillArea();
  ~Canvas();
};

} // namespace core