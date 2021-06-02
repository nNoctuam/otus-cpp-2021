#pragma once

#include "models.h"
#include <memory>

class Canvas {
public:
  void DrawLine();
  void DrawCurve();
  void FillArea();
  void DrawSomeOtherPrimitive();
};

class IShape {
public:
  void Render(std::weak_ptr<Canvas> canvas);
  void Resize(double scale);
  void Move(Point newPosition);
  friend class DocumentSerializer;
};