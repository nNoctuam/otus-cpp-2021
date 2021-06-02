#pragma once

#include "basics.h"
#include <string>

namespace gui {

class TextInput : public IInterfaceElement {
public:
  TextInput(const std::string &id, const std::string &text)
      : _id(id), _text(text) {}
  void OnClick() override;
  std::string Text();
  ~TextInput() override;

private:
  std::string _id;
  std::string _text;
};

class Button : public IInterfaceElement {
public:
  Button(const std::string &id, const std::string &title)
      : _id(id), _title(title) {}
  void OnClick() override;
  ~Button() override;

private:
  std::string _id;
  std::string _title;
};

} // namespace gui