#pragma once

#include "../core/Data.h"
#include "../core/Document.h"
#include "memory"

namespace services {

template <typename T>
class IDocumentSerializer {
  T Serialize(const core::Document &);
  std::shared_ptr<core::Document> Unserialize(T);
};

} // namespace services