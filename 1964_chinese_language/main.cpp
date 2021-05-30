#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  long population, dialects;
  std::cin >> population >> dialects;

  std::vector<long> dialectSpeakers;
  dialectSpeakers.reserve(dialects);

  long v;
  for (long i = 0; i < dialects; i++) {
    std::cin >> v;
    dialectSpeakers.push_back(v);
  }

  std::sort(dialectSpeakers.begin(), dialectSpeakers.end(),
            [](long a, long b) { return a > b; });

  long polyglots = dialectSpeakers[0];
  for (long i = 1; i < dialects; i++) {
    polyglots = polyglots + dialectSpeakers[i] - population;
    if (polyglots <= 0) {
      break;
    }
  }

  std::cout << (polyglots > 0 ? polyglots : 0) << std::endl;

  return 0;
}