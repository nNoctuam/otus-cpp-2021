#pragma once

#include "../../../core/gui/IView.h"
#include "../../inputs/ColorPicker.h"

namespace gui {

class ColorPickerView : public core::gui::IView {
public:
  ColorPickerView(const std::weak_ptr<ColorPicker> &model) : _model(model) {}
  void Render() override;

private:
  std::weak_ptr<ColorPicker> _model;
};

} // namespace gui
