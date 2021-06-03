#pragma once
#include "../core/gui/IController.h"
#include "../core/Document.h"
#include "../controllers/CMainMenu.h"

namespace gui {

class CMainWindow : public core::gui::IController {
public:
  void Run() override {}

private:
  std::shared_ptr<CMainMenu> _mainMenuController;
  std::shared_ptr<core::Document> _document;
};

}