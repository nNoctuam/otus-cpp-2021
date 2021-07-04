#pragma once

#include <map>
#include <vector>

template <typename T, T DEFAULT_VALUE> class Storage {
public:
  T get(const std::vector<int> &key) const {
    if (_storage.find(key) == _storage.end()) {
      return DEFAULT_VALUE;
    }
    return _storage.at(key);
  }

  void set(const std::vector<int> &key, T value) {
    if (value == DEFAULT_VALUE) {
      _storage.erase(key);
    } else {
      _storage[key] = value;
    }
  }

  size_t size() const { return _storage.size(); }

  auto begin() { return _storage.begin(); }

  auto end() { return _storage.end(); }

private:
  std::map<std::vector<int>, T> _storage;
};