#include <array>
#include <iostream>
#include "algorithm"

int main() {
  int n;
  std::array<char, 2> position{};
  std::string line;

  std::cin >> n;
  std::cin.get();
  for (int i = 0; i < n; i++) {
    std::getline(std::cin, line);

    int top = std::min(2, line[0] - 'a');
    int bottom = std::min(2, 'h' - line[0]);
    int right = std::min(2, 8 - (line[1] - '0'));
    int left = std::min(2, line[1] - '1');

    int positions = 0
      + (top == 2 && left > 0 ? 1 : 0)
      + (top == 2 && right > 0 ? 1 : 0)
      + (bottom == 2 && left > 0 ? 1 : 0)
      + (bottom == 2 && right > 0 ? 1 : 0)
      + (top > 0 && left == 2 ? 1 : 0)
      + (top > 0 && right == 2 ? 1 : 0)
      + (bottom > 0 && left == 2 ? 1 : 0)
      + (bottom > 0 && right == 2 ? 1 : 0);
    std::cout << positions << std::endl;

  }

  return 0;
}