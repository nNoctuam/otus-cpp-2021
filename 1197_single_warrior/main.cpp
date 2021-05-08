#include <iostream>

int main() {
  int a, b, c;
  std::cin >> a >> b >> c;
  int x1 = a - b * c;
  int x2 = a - b - c;
  std::cout << (x1 < x2 ? x1 : x2) << std::endl;

  return 0;
}