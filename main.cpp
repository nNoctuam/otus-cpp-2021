#include <map>
#include <memory>
#include <vector>

#include <iostream>

template <typename T, T DEFAULT_VALUE> class Storage {
public:
  T get(const std::vector<int> &key) const {
    if (_storage.find(key) == _storage.end()) {
      return DEFAULT_VALUE;
    }
    return _storage.at(key);
  }
  void set(const std::vector<int> &key, T value) {
    printf("storage set %d\n", value);
    if (value == DEFAULT_VALUE) {
      _storage.erase(key);
    } else {
      _storage[key] = value;
    }
    printf("storage size after set is %lu, ", _storage.size());
    printf("storage address is %p\n", (void*)&_storage);
  }

  int size() const {
    printf("storage address is %p\n", (void*)&_storage);
    return _storage.size();
  }

private:
  std::map<std::vector<int>, T> _storage;
};




template <typename T, T DEFAULT_VALUE, int DIMENSIONS = 2> class Matrix {
  static_assert(DIMENSIONS > 0, "");

public:
  explicit Matrix() : _storage(std::make_shared<Storage<T, DEFAULT_VALUE>>()) {}
  Matrix(std::shared_ptr<Storage<T, DEFAULT_VALUE>> storage, std::vector<int> key) : _storage(storage), _key(std::move(key)) {}

  Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1> &operator[](int i) {
    printf("Matrix<%d>[%d]\n", DIMENSIONS, i);
    if (_matrix.find(i) == _matrix.end()) {
      std::vector<int> childKey;
      std::copy(_key.begin(), _key.end(), childKey);
      childKey.push_back(i);
      auto child = new Matrix<T, DEFAULT_VALUE, DIMENSIONS-1>(_storage, childKey);
      // fixme: invalid conversion from ‘Matrix<int, -1, 0>*’ to ‘int’
      _matrix[i] = child;
    }
    return _matrix[i];
  }

  int size() const { return _storage->size(); }

private:
  std::map<int, Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>> _matrix;
  std::shared_ptr<Storage<T, DEFAULT_VALUE>> _storage;
  const std::vector<int> _key;
};




template <typename T, T DEFAULT_VALUE> class Matrix<T, DEFAULT_VALUE, 0> {
public:


  Matrix<T, DEFAULT_VALUE, 0> &operator=(const T &value) {
    printf("set %d\n", value);
    _storage->set(_key, value);
    return *this;
  }

   Matrix<T, DEFAULT_VALUE, 0>& operator=(Matrix<T, DEFAULT_VALUE, 0> &&other) noexcept {
    _key = std::move(other._key);
    _storage = other._storage;
  }




  bool operator == (const T& other) const {
    return _storage->get(_key) == other;
  }

  bool operator == (T other) const {
    return _storage->get(_key) == other;
  }

  operator T() const {
    return _storage->get(_key);
  }

  int size() { return _storage->size(); }

private:
  Matrix(std::shared_ptr<Storage<T, DEFAULT_VALUE>> storage,
         const std::vector<int> &key)
      : _storage(storage), _key(key) {}

  std::shared_ptr<Storage<T, DEFAULT_VALUE>> _storage;
  const std::vector<int> _key;

  friend class Matrix<T, DEFAULT_VALUE, 1>;
};

// todo set -1 -> remove from storage completely
// todo return default value if not found in storage

int main(int, char **) {
  Matrix<int, -1, 1> m;
  m[5] = 15;
//  m[10005] = 25;
//  m[10005] = -1;
  std::cout << m[5] << " size=" << m.size() << std::endl;

//  Matrix<int, -1, 2> m2;
//  m2[3][5] = 35;
//  m2[1][151515] = 5123231;
//  std::cout << m2[3][5] << " size=" << m.size() << std::endl;

  return 0;
}
