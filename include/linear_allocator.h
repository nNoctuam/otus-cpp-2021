#include "cstdlib"
#include "iostream"

#ifndef LINEAR_ALLOCATOR_H
#define LINEAR_ALLOCATOR_H

template <typename T> class LinearAllocator {
public:
  using value_type = T;

  constexpr static int INITIAL_SIZE = 10;

  LinearAllocator();

  template <typename C>
  explicit LinearAllocator(const LinearAllocator<C> &) noexcept;

  T *allocate(std::size_t n);

  void deallocate(T *p, std::size_t n);

  template <typename U, typename... Args> void construct(U *p, Args &&...args);

  void destroy(T *p);

  void printAvailabilityMap();

  template <typename U> struct rebind { using other = LinearAllocator<U>; };

  ~LinearAllocator() noexcept;

private:
  T *_heap = nullptr;
  bool _blocksAvailability[INITIAL_SIZE] = {};
};

#include "../src/linear_allocator.tpp"

#endif
