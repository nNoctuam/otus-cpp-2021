#pragma once
#include "../../core/gui/IClickable.h"
#include "../../core/gui/IGUIElement.h"
#include "../../core/gui/models/IContainer.h"
#include "string"

namespace gui {

class MenuEntry : public core::gui::IGUIElement, public core::gui::IClickable {
public:
  std::string title;
  ~MenuEntry() override;
};

class Menu : core::gui::IContainer {};

} // namespace gui