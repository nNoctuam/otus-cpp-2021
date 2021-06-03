#pragma once

#include "../../../core/gui/IView.h"
#include "../../inputs/TextInput.h"

namespace gui {

class TextInputView : public core::gui::IView {
public:
  TextInputView(const std::weak_ptr<TextInput> &model) : _model(model) {}
  void Render() override;

private:
  std::weak_ptr<TextInput> _model;
};

} // namespace gui
