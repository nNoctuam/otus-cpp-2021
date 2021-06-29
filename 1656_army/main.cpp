#include <algorithm>
#include <iostream>
#include <map>
#include <cmath>
#include <vector>

int main() {
  int n;
  std::cin >> n;

  std::vector<int> heights;
  heights.resize(n * n);
  for (int i = 0; i < n * n; i++) {
    std::cin >> heights[i];
  }

  std::vector<std::vector<int>> matrix;
  matrix.resize(n);
  for (int i = 0; i < n; i++) {
    matrix[i].resize(n);
  }

  std::sort(heights.begin(), heights.end());

  std::map<std::pair<int, int>, double> distances;
  std::vector<std::pair<int, int>> order;
  order.reserve(n * n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      distances[std::pair<int, int>(i, j)] =
          std::sqrt((i * 2 - n + 1) * (i * 2 - n + 1) +
                    (j * 2 - n + 1) * (j * 2 - n + 1));
//      std::cout << i << ":" << j << "=" << distances[std::pair<int, int>(i, j)]
//                << std::endl;
      order.emplace_back(std::pair<int, int>(i, j));
    }
  }

  std::sort(order.rbegin(), order.rend(),
            [&distances](std::pair<int, int> p1, std::pair<int, int> p2) {
              return distances[p1] < distances[p2];
            });

//  for (const auto p : order) {
//    std::cout << p.first << ":" << p.second << std::endl;
//  }

  for (int i = 0; i < n * n; i++) {
//    std::printf("set #%d (%d:%d) = %d\n", i, order[i].first, order[i].second,
//                heights[i]);
    matrix[order[i].first][order[i].second] = heights[i];
  }

//  for (const int i : heights) {
//    std::cout << i << " ";
//  }

//  std::cout << std::endl;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << matrix[i][j] << "\t";
    }
    std::cout << std::endl;
  }

  return 0;
}

// 6 5 4 4 5 6
// 5 3 2 2 3 5
// 4 2 1 1 2 4
// 4 2 1 1 2 4
// 5 3 2 2 3 5
// 6 5 4 4 5 6

// 6 5 4 5 6
// 5 3 2 3 5
// 4 2 1 2 4
// 5 3 2 3 5
// 6 5 4 5 6
