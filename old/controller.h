#pragma once
#include "app.h"
#include "core/gui.h"
#include "core/models.h"
#include "service/service.h"

class SaveDocumentForm : public Form {
public:
  explicit SaveDocumentForm(Application& app) : _app(app) {
    _pathInput =
        std::make_shared<TextInput>("newDocumentPath", "/tmp/image.dat");
    AddElement(_pathInput);
  }
  void OnSubmit() override {
    auto path = _pathInput->Text();
    _app.SaveTo(path);
  };
  void OnCancel() override;

private:
  Application _app;
  std::shared_ptr<TextInput> _pathInput;
};

class SaveMenuEntry : public MenuEntry {
public:
  std::string name = "Save";

  explicit SaveMenuEntry(Application& app) : _app(app){};
  void OnClick() override {
    auto dialog = std::make_shared<Dialog>();
    dialog->AddElement(std::make_shared<SaveDocumentForm>(_app));
    _app.AddElement(dialog);
  }
  ~SaveMenuEntry() override;

private:
  Application _app;
};
