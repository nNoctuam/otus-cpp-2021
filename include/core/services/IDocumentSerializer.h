#pragma once

#include "../Data.h"
#include "../Document.h"
#include "memory"

namespace core {
namespace services {

template <typename T>
class IDocumentSerializer {
  T Serialize(const core::Document &);
  std::shared_ptr<core::Document> Unserialize(T);
};

} // namespace services
} // namespace core