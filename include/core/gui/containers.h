#pragma once

#include "basics.h"
#include <memory>
#include <string>
#include <vector>
namespace gui {

class Container : public IInterfaceElement {
public:
  Container();
  void OnClick() override; // pass click to inner elements
  void AddElement(std::shared_ptr<IInterfaceElement> element);
  std::weak_ptr<IInterfaceElement> getByID(std::string id);
  virtual ~Container();

private:
  std::vector<IInterfaceElement> _elements;
};

class Form : public Container {
public:
  virtual void OnSubmit() = 0;
  virtual void OnCancel() = 0;
};

class Dialog : public Container {
public:
  void Show();
  void Close();
};

} // namespace gui