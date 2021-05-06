
template <typename T, typename Allocator>
DummyArray<T, Allocator>::DummyArray() {
  _elements = new T *[_capacity];
}

template <typename T, typename Allocator>
DummyArray<T, Allocator>::~DummyArray() {
  delete[] _elements;
}

template <typename T, typename Allocator>
void DummyArray<T, Allocator>::push(T value) {
  if (_current == _capacity) {
    T **tmp = new T *[_capacity * 2];
    for (int i = 0; i < _capacity; i++) {
      tmp[i] = _elements[i];
    }
    delete[] _elements;
    _elements = tmp;
    _capacity *= 2;
  }
  auto *memBlock = _allocator.allocate(size_t(1));
  _elements[_current] = new (memBlock) T(value);
  _current++;
}

template <typename T, typename Allocator> void DummyArray<T, Allocator>::pop() {
  if (_current == 0) {
    throw std::runtime_error("pop on empty DummyArray");
  }
  _allocator->deallocate(_elements[_current - 1], 1);
  _current--;
}

template <typename T, typename Allocator>
void DummyArray<T, Allocator>::clear() {
  for (int i = 0; i < _current; i++) {
    delete _elements[i];
  }
}

template <typename T, typename Allocator>
const T &DummyArray<T, Allocator>::get(int index) {
  return *_elements[index];
}

template <typename T, typename Allocator>
T &DummyArray<T, Allocator>::operator[](int index) {
  return *_elements[index];
}

template <typename T, typename Allocator>
int DummyArray<T, Allocator>::capacity() {
  return _capacity;
}

template <typename T, typename Allocator> int DummyArray<T, Allocator>::size() {
  return _current;
}

template <typename T, typename Allocator>
bool DummyArray<T, Allocator>::empty() {
  return _current == 0;
}

template <typename T, typename Allocator>
void DummyArray<T, Allocator>::print() {
  for (int i = 0; i < _current; i++) {
    std::cout << std::to_string(*_elements[i]) << " ";
  }
  std::cout << std::endl;
}
