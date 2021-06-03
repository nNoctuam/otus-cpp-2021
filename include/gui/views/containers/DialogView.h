#pragma once

#include "../../../core/gui/IView.h"
#include "../../containers/Dialog.h"

namespace gui {

class DialogView : public core::IView {
public:
  DialogView(const std::weak_ptr<Dialog> &model) : _model(model) {}
  void Render() override;

private:
  std::weak_ptr<Dialog> _model;
};

} // namespace gui
