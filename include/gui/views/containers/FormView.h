#pragma once

#include "../../../core/gui/IView.h"
#include "../../containers/Form.h"

namespace gui {

class FormView : public core::IView {
public:
  FormView(const std::weak_ptr<Form> &model) : _model(model) {}
  void Render() override;

private:
  std::weak_ptr<Form> _model;
};

} // namespace gui
