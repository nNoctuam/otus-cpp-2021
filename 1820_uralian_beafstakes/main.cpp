#include <iostream>

int main() {
  int n, k;
  std::cin >> n >> k;
  if (n <= k) {
    std::cout << 2 << std::endl;
  } else {
    std::cout << n * 2 / k + ((2 * n % k) > 0 ? 1 : 0) << std::endl;
  }

  return 0;
}