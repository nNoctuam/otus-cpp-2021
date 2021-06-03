#pragma once

#include "memory"
#include "vector"

namespace core {
namespace services {

template <typename T> class IDataSaver {
  void Save(const T &);
  T Load();
};

} // namespace services
} // namespace core