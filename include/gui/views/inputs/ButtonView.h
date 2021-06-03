#pragma once

#include "../../../core/gui/IView.h"
#include "../../inputs/Button.h"

namespace gui {

class ButtonView : public core::IView {
public:
  ButtonView(const std::weak_ptr<Button> &model) : _model(model) {}
  void Render() override;

private:
  std::weak_ptr<Button> _model;
};

} // namespace gui
