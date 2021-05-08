#include "cstdlib"
#include "iostream"

#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

template <typename T, int INITIAL_SIZE = 10> class LinearAllocator {
public:
  using value_type = T;

  LinearAllocator() = default;

  template <typename C>
  explicit LinearAllocator(const LinearAllocator<C> &) noexcept {
    std::cout << "[LinearAllocator] copying constructor" << std::endl;
  }

  T *allocate(std::size_t n) {
    if (_heap == nullptr) {
      reserveMemory();
    }

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

  void reserveMemory() {
    _heap = static_cast<T *>(malloc(INITIAL_SIZE * sizeof(T)));
    _blocksAvailability.reserve(INITIAL_SIZE);
    _blocksAvailability.resize(INITIAL_SIZE);
    std::fill(_blocksAvailability.begin(), _blocksAvailability.end(), true);
  }

  void deallocate(T *p, std::size_t n) {
    for (size_t i = 0; i < n; i++) {
      _blocksAvailability[p - _heap + i] = true;
    }
  }

  template <typename U, typename... Args> void construct(U *p, Args &&...args) {
    new (p) U(std::forward<Args>(args)...);
  }

  void destroy(T *p) { p->~T(); }

  void printAvailabilityMap() {
    std::cout << "[LinearAllocator] ";
    for (bool b : _blocksAvailability) {
      std::cout << (b ? '_' : 'x') << " ";
    }
    std::cout << std::endl;
  }

  template <typename U> struct rebind { using other = LinearAllocator<U>; };

  ~LinearAllocator() noexcept { free(_heap); }

private:
  T *_heap = nullptr;
  std::vector<bool> _blocksAvailability;
};

template <class T, class U>
constexpr bool operator==(const LinearAllocator<T> &a,
                          const LinearAllocator<U> &b) noexcept {
  return false;
}

template <class T, class U>
constexpr bool operator!=(const LinearAllocator<T> &a,
                          const LinearAllocator<U> &b) noexcept {
  return true;
}

#endif
