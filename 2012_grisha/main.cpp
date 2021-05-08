#include <iostream>

int main() {
  int n;
  std::cin >> n;
  std::cout << ((12 - n) <= 4 * 60 / 45 ? "YES" : "NO") << std::endl;

  return 0;
}