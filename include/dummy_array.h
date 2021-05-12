#ifndef DUMMY_ARRAY_H
#define DUMMY_ARRAY_H

template <typename T, typename Allocator = std::allocator<T>> class DummyArray {
public:
  DummyArray() { _elements = new T *[_capacity]; }

  ~DummyArray() { delete[] _elements; }

  struct Iterator {
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = T *;
    using reference = T &;

    explicit Iterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }

    pointer operator->() { return m_ptr; }

    Iterator &operator++() {
      m_ptr++;
      return *this;
    }

    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }

    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_ptr == b.m_ptr;
    };

    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_ptr != b.m_ptr;
    };

  private:
    pointer m_ptr;
  };

  void push(T value) {
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

  void pop() {
    if (_current == 0) {
      throw std::runtime_error("pop on empty DummyArray");
    }
    _allocator->deallocate(_elements[_current - 1], 1);
    _current--;
  }

  void clear() {
    for (int i = 0; i < _current; i++) {
      delete _elements[i];
    }
  }

  Iterator begin() { return Iterator(_elements[0]); }

  Iterator end() {
    return Iterator(_current == _capacity ? _elements[_current - 1] + 1
                                          : _elements[_current]);
  }

  const T &get(int index) { return *_elements[index]; }

  T &operator[](int index) { return *_elements[index]; }

  int capacity() { return _capacity; }

  int size() { return _current; }

  bool empty() { return _current == 0; }

  void print() {
    for (int i = 0; i < _current; i++) {
      std::cout << std::to_string(*_elements[i]) << " ";
    }
    std::cout << std::endl;
  }

private:
  Allocator _allocator;
  int _current = 0;
  int _capacity = 10;
  T **_elements;
};

#endif
