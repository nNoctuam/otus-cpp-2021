#pragma once

#include "../../../core/gui/IView.h"
#include "../../containers/Menu.h"

namespace gui {

class MenuView : public core::IView {
public:
  MenuView(const std::weak_ptr<Menu> &model) : _model(model) {}
  void Render() override;

private:
  std::weak_ptr<Menu> _model;
};

} // namespace gui
