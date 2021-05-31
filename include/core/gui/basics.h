#pragma once

#include "../models.h"

namespace gui {

class IClickable {
public:
  virtual void OnClick() = 0;
};

class IInterfaceElement : public IClickable {
public:
  virtual ~IInterfaceElement();
  Point position;
};

} // namespace gui