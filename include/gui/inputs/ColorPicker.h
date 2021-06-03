#pragma once
#include "../../core/gui/models/IInput.h"

namespace gui {

class ColorPicker : public core::IInput<std::string> {
public:
  ~ColorPicker();

  std::string GetValue() override;
  void SetValue(std::string t) override;

  std::string GetTitle();

private:
  std::string _title;
  std::string _value;
};

} // namespace gui
