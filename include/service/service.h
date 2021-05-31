#pragma once
#include <memory>
#include <vector>
#include "../core/document.h"

class DocumentSerializer {
public:
  std::vector<int8_t> Serialize(const Document &document);
  std::unique_ptr<Document> Unserialize(std::vector<int8_t>);
};

class DataSaver {
public:
  void Save(std::string path, std::vector<int8_t>);
  std::vector<int8_t> Load(std::string path);
};