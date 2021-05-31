#pragma once
#include "graphics.h"
#include "memory"
#include "string"
#include <array>
#include <list>
#include <vector>

class Document {
public:
  Document(Canvas& canvas);
  void AddShape(std::shared_ptr<IShape> shape);
  ~Document();

private:
  Canvas canvas;
  std::list<std::shared_ptr<IShape>> _shapes;
  friend class DocumentSerializer;
};
