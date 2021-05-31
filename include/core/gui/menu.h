#pragma once

#include "basics.h"
#include <memory>
#include <string>

namespace gui {

class MenuEntry : IInterfaceElement {
public:
  std::string name;
  ~MenuEntry() override;
};

class Menu : public Container {
public:
  Menu();
  void AddEntry(std::shared_ptr<MenuEntry> entry);
  ~Menu() override;
};

} // namespace gui