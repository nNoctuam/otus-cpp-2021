#pragma once
#include "../core/gui/IController.h"
#include "../gui/inputs/Button.h"

namespace gui {

class CForm : public core::IController {
public:
  void Run() override {}

private:
  std::shared_ptr<Button> _submitButton;
  std::shared_ptr<Button> _cancelButton;
  std::shared_ptr<FormView> _view;
};

}