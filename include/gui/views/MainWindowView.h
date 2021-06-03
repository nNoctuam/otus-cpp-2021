#pragma once

#include "../../core/gui/IView.h"
#include "../containers/MainWindow.h"

namespace gui {

class MainWindowView : public core::gui::IView {
public:
  MainWindowView(const std::weak_ptr<MainWindow> &model) : _model(model) {}
  void Render() override;

private:
  std::weak_ptr<MainWindow> _model;
};

} // namespace gui
