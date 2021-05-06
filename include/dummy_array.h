#ifndef DUMMY_ARRAY_H
#define DUMMY_ARRAY_H

template <typename T, typename Allocator = std::allocator<T>> class DummyArray {
public:
  DummyArray();

  ~DummyArray();

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

  void push(T value);

  void pop();

  void clear();

  Iterator begin() { return Iterator(_elements[0]); }

  Iterator end() {
    return Iterator(_current == _capacity ? _elements[_current - 1] + 1
                                          : _elements[_current]);
  }

  const T &get(int index);

  T &operator[](int index);

  int capacity();

  int size();

  bool empty();

  void print();

private:
  Allocator _allocator;
  int _current = 0;
  int _capacity = 10;
  T **_elements;
};

#include "../src/dummy_array.tpp"

#endif
