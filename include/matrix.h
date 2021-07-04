#pragma once

#include <map>
#include <memory>
#include <vector>
#include "storage.h"


template <typename T, T DEFAULT_VALUE, int DIMENSIONS = 2> class Matrix {
  static_assert(DIMENSIONS > 0);

public:
  explicit Matrix() : _storage(std::make_shared<Storage<T, DEFAULT_VALUE>>()) {}
  Matrix(std::shared_ptr<Storage<T, DEFAULT_VALUE>> storage,
         std::vector<int> position)
      : _storage(storage), _position(std::move(position)) {}

  Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1> &operator[](int i) {
    std::vector<int> child_position;
    std::copy(_position.begin(), _position.end(), std::back_inserter(child_position));
    child_position.push_back(i);
    return *(new Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>(_storage, child_position));
  }

  size_t size() const { return _storage->size(); }

  auto begin() { return _storage->begin(); }

  auto end() { return _storage->end(); }

private:
  std::shared_ptr<Storage<T, DEFAULT_VALUE>> _storage;
  const std::vector<int> _position;
};

template <typename T, T DEFAULT_VALUE> class Matrix<T, DEFAULT_VALUE, 0> {
public:
  Matrix<T, DEFAULT_VALUE, 0> &operator=(const T &value) {
    _storage->set(_position, value);
    return *this;
  }

  Matrix<T, DEFAULT_VALUE, 0> &
  operator=(Matrix<T, DEFAULT_VALUE, 0> &&other) noexcept {
    _position = std::move(other._position);
    _storage = other._storage;
  }

  bool operator==(const T &other) const { return _storage->get(_position) == other; }

  explicit operator T() const { return _storage->get(_position); }

  friend std::ostream &operator<<(std::ostream &out,
                                  const Matrix<T, DEFAULT_VALUE, 0> &matrix) {
    out << matrix._storage->get(matrix._position);
    return out;
  }

private:
  Matrix(std::shared_ptr<Storage<T, DEFAULT_VALUE>> storage,
         std::vector<int> key)
      : _storage(storage), _position(std::move(key)) {}

  std::shared_ptr<Storage<T, DEFAULT_VALUE>> _storage;
  const std::vector<int> _position;

  friend class Matrix<T, DEFAULT_VALUE, 1>;
};
