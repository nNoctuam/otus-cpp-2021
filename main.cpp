#include "include/lib.h"

#include <iostream>
#include <map>
#include <stdexcept>
#include <vector>

#include "include/dummy_array.h"
#include "include/linear_allocator.h"

int main(int, char **) {
  // region simple map
  std::cout << "MAP ====================================" << std::endl;
  std::map<int, int> map;
  map[0] = 0;
  map[1] = 1;
  for (int i = 2; i < 10; i++) {
    map[i] = map[i - 1] * i;
  }
  for (const auto &item : map) {
    std::cout << item.first << " " << item.second << " " << std::endl;
  }
  std::cout << std::endl;
  // endregion

  // region map with custom allocator
  std::cout << "MAP WITH LA ============================" << std::endl;
  auto mapLA = std::map<int, int, std::less<>,
                        LinearAllocator<std::pair<const int, int>>>{};
  mapLA[0] = 0;
  mapLA[1] = 1;
  for (int i = 2; i < 10; i++) {
    mapLA[i] = mapLA[i - 1] * i;
  }
  for (const auto &item : mapLA) {
    std::cout << item.first << " " << item.second << " " << std::endl;
  }
  std::cout << std::endl;
  // endregion

  // region DummyArray
  std::cout << "DUMMY ARRAY ============================" << std::endl;
  auto list = new DummyArray<int, std::allocator<int>>();
  for (int i = 0; i < 10; i++) {
    list->push(i);
  }
  for (int i = 0; i < 10; i++) {
    std::cout << list->get(i) << std::endl;
  }
  std::cout << std::endl;
  // endregion

  // region DummyArray with LinearAllocator
  std::cout << "DUMMY ARRAY WITH LA ====================" << std::endl;
  DummyArray<int, LinearAllocator<int>> listLA;
  for (int i = 0; i < 10; i++) {
    listLA.push(i);
  }

  for (auto i : listLA) {
    std::cout << i << std::endl;
  }
  // endregion

  return 0;
}
