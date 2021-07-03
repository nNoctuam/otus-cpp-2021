#include <map>
#include <memory>
#include <vector>

#include <iostream>

template <typename T, T DEFAULT_VALUE, int DIMENSIONS = 2> class Matrix {
  static_assert(DIMENSIONS > 1, "");

public:
  Matrix() : _storage(std::make_shared<std::map<std::vector<int>, T>>()) {}

  Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1> operator[](int i) {
    printf("Matrix<%d>[%d]\n", DIMENSIONS, i);
    return _matrix[i];
  }

  int size() {
    return _storage->size();
  }

private:
  std::map<int, Matrix<T, DEFAULT_VALUE, DIMENSIONS - 1>> _matrix;
  std::shared_ptr<std::map<std::vector<int>, T>> _storage;
};

template <typename T, T DEFAULT_VALUE> class Matrix<T, DEFAULT_VALUE, 1> {
public:
  Matrix() : _storage(std::make_shared<std::map<std::vector<int>, T>>()) {}

  T &operator[](int i) {
    printf("Matrix<%d>[%d]\n", 1, i);
    std::vector<int> key;
    std::copy(_parentKey.begin(), _parentKey.end(), std::back_inserter(key));
    key.push_back(i);

    return (*_storage)[key];
  }

  int size() {
    return _storage->size();
  }

private:
  Matrix(std::shared_ptr<std::map<std::vector<int>, T>> storage,
         const std::vector<int> &parentKey)
      : _storage(storage), _parentKey(parentKey) {}

  std::shared_ptr<std::map<std::vector<int>, T>> _storage;
  const std::vector<int> _parentKey;
};

// todo set -1 -> remove from storage completely
// todo return default value if not found in storage

int main(int, char **) {
  Matrix<int, -1, 1> m;
  m[5] = 15;
  m[10005] = 25;
  std::cout << m[5] << " size=" << m.size() << std::endl;

  Matrix<int, -1, 2> m2;
  m2[3][5] = 35;
  m2[1][151515] = 5123231;
  std::cout << m2[3][5] << " size=" << m.size() << std::endl;

  return 0;
}
