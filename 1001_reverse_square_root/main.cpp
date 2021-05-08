#include <cmath>
#include <iostream>
#include <vector>

int main() {
  std::vector<long long> ints;
  ints.reserve(10);

  long long i;
  while (std::cin >> i) {
    ints.push_back(i);
  }

  for (auto p = ints.cend() - 1, start = ints.cbegin(); p >= start; p--) {
    printf("%.4f\n", sqrt(*p));
  }

  return 0;
}