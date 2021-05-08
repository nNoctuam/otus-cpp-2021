#include <array>
#include <iostream>
#include <vector>

int main() {
  std::vector<std::pair<int, std::string>> quantitatives{
      std::make_pair(1, "few"),
      std::make_pair(5, "several"),
      std::make_pair(10, "pack"),
      std::make_pair(20, "lots"),
      std::make_pair(50, "horde"),
      std::make_pair(100, "throng"),
      std::make_pair(250, "swarm"),
      std::make_pair(500, "zounds"),
      std::make_pair(1000, "legion"),
  };

  int n;
  std::cin >> n;

  for (auto p = quantitatives.cend()-1, start = quantitatives.cbegin(); p >= start; p--) {
    if (n >= (*p).first) {
      std::cout << (*p).second << std::endl;
      break;
    }
  }

  return 0;
}