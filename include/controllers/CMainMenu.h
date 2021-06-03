#pragma once
#include "../core/gui/IController.h"
#include "../gui/containers/Menu.h"

namespace gui {

class CMainMenu : public core::IController {
public:
  void Run() override {}

private:
  std::shared_ptr<Menu> _menu;
  std::shared_ptr<MenuView> _view;
};

}