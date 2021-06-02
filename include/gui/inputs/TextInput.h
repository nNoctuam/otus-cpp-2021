#pragma once
#include "../../core/gui/models/IInput.h"

namespace gui {

class TextInput : public core::gui::IInput<std::string> {
public:
  ~TextInput();

  std::string GetValue() override;
  void SetValue(std::string t) override;

private:
  std::string _value;
};

} // namespace gui
