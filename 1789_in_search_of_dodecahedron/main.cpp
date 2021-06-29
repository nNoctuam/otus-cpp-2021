#include <iostream>

int main() {
  int m;
  std::cin >> m;

  std::cout << 2 * m - 1 << std::endl;

  for (int i = 1; i <= m; i++) {
    std::cout << i << " ";
  }
  for (int i = m; i > 1; i--) {
    std::cout << i << " ";
  }

  return 0;
}