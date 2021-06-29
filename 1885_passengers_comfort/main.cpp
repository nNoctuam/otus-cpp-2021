#include <iostream>

int main() {
  int h, t, v, x;
  std::cin >> h >> t >> v >> x;

  double min = std::max(0.0, double(h - x * t) / (v - x));
  double max = double(h) / std::max(double(x), double(h)/t);

  std::printf("%.8f %.8f", min, max);
  return 0;
}