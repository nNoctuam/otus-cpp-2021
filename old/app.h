#pragma once
#include "core/document.h"
#include "core/gui.h"
#include "core/models.h"
#include "service/service.h"

class Application : public gui::Container {
public:
  struct Services {
    DocumentSerializer documentSerializer;
    DataSaver dataSaver;
  };

  struct Data {};

  explicit Application(Document& document)
      : document(document), services(), data(){};
  ~Application();

  void SaveTo(std::string path);
  void LoadFrom(std::string path);

  Document document;
  Services services;
  Data data;

private:
};