#pragma once

#include <map>
#include <memory>
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

  int size() const { return _storage.size(); }

  auto begin() { return _storage.begin(); }

  auto end() { return _storage.end(); }

private:
  std::map<std::vector<int>, T> _storage;
};

template <typename T, T DEFAULT_VALUE, int DIMENSIONS = 2> class Matrix {
  static_assert(DIMENSIONS > 0, "");

public:
  explicit Matrix() : _storage(std::make_shared<Storage<T, DEFAULT_VALUE>>()) {}
  Matrix(std::shared_ptr<Storage<T, DEFAULT_VALUE>> storage,
         std::vector<int> key)
      : _storage(storage), _key(std::move(key)) {}

  Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1> &operator[](int i) {
    std::vector<int> childKey;
    std::copy(_key.begin(), _key.end(), std::back_inserter(childKey));
    childKey.push_back(i);
    return *(new Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>(_storage, childKey));
  }

  int size() const { return _storage->size(); }

  auto begin() { return _storage->begin(); }

  auto end() { return _storage->end(); }

private:
  std::shared_ptr<Storage<T, DEFAULT_VALUE>> _storage;
  const std::vector<int> _key;
};

template <typename T, T DEFAULT_VALUE> class Matrix<T, DEFAULT_VALUE, 0> {
public:
  Matrix<T, DEFAULT_VALUE, 0> &operator=(const T &value) {
    _storage->set(_key, value);
    return *this;
  }

  Matrix<T, DEFAULT_VALUE, 0> &
  operator=(Matrix<T, DEFAULT_VALUE, 0> &&other) noexcept {
    _key = std::move(other._key);
    _storage = other._storage;
  }

  bool operator==(const T &other) const { return _storage->get(_key) == other; }

  explicit operator T() const { return _storage->get(_key); }

  friend std::ostream &operator<<(std::ostream &out,
                                  const Matrix<T, DEFAULT_VALUE, 0> &matrix) {
    out << matrix._storage->get(matrix._key);
    return out;
  }

private:
  Matrix(std::shared_ptr<Storage<T, DEFAULT_VALUE>> storage,
         std::vector<int> key)
      : _storage(storage), _key(std::move(key)) {}

  std::shared_ptr<Storage<T, DEFAULT_VALUE>> _storage;
  const std::vector<int> _key;

  friend class Matrix<T, DEFAULT_VALUE, 1>;
};
