#include "../include/linear_allocator.h"
#include "iostream"

template <typename T> void LinearAllocator<T>::printAvailabilityMap() {
  std::cout << "[LinearAllocator] ";
  for (bool b : _blocksAvailability) {
    std::cout << (b ? '_' : 'x') << " ";
  }
  std::cout << std::endl;
}

template <typename T> LinearAllocator<T>::LinearAllocator() {
  _heap = static_cast<T *>(malloc(INITIAL_SIZE * sizeof(T)));
  for (size_t i = 0; i < INITIAL_SIZE; i++) {
    _blocksAvailability[i] = true;
  }
}

template <typename T>
template <typename C>
LinearAllocator<T>::LinearAllocator(const LinearAllocator<C> &) noexcept {
  std::cout << "[LinearAllocator] copying constructor" << std::endl;
}

template <typename T> T *LinearAllocator<T>::allocate(std::size_t n) {
  bool isSequenceFree;
  size_t position = 0, i;
  while (position <= INITIAL_SIZE + n) {
    isSequenceFree = true;
    for (i = 0; i < n; i++) {
      if (!_blocksAvailability[position]) {
        position += n;
        isSequenceFree = false;
        break;
      }
    }
    if (!isSequenceFree) {
      continue;
    }

    for (i = 0; i < n; i++) {
      _blocksAvailability[i + position] = false;
    }
    return reinterpret_cast<T *>(_heap + position);
  }

  throw std::runtime_error(
      "[LinearAllocator] cannot allocate memory! requested size=" +
      std::to_string(n));
}

template <typename T> void LinearAllocator<T>::deallocate(T *p, std::size_t n) {
  for (size_t i = 0; i < n; i++) {
    _blocksAvailability[p - _heap + i] = true;
  }
}

template <typename T>
template <typename U, typename... Args>
void LinearAllocator<T>::construct(U *p, Args &&...args) {
  new (p) U(std::forward<Args>(args)...);
}

template <typename T> void LinearAllocator<T>::destroy(T *p) { p->~T(); }

template <typename T> LinearAllocator<T>::~LinearAllocator() noexcept {
  free(_heap);
}

template <class T, class U>
constexpr bool operator==(const LinearAllocator<T> &a,
                          const LinearAllocator<U> &b) noexcept {
  return a._heap == b._heap && a.value_type == b.value_type;
}

template <class T, class U>
constexpr bool operator!=(const LinearAllocator<T> &a,
                          const LinearAllocator<U> &b) noexcept {
  return a._heap != b._heap || a.value_type != b.value_type;
}