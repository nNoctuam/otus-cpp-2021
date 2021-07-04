#include "include/matrix.h"
#include <iostream>

int main(int, char **) {
  Matrix<int, 0, 2> matrix;
  for (int i = 0; i < 10; i++) {
    matrix[i][i] = i;
    matrix[i][9 - i] = 9 - i;
  }

  for (int i = 1; i < 9; i++) {
    for (int j = 1; j < 9; j++) {
      std::cout << matrix[i][j] << " ";
    }

    std::cout << std::endl;
  }
  std::cout << std::endl;

  std::cout << "size = " << matrix.size() << std::endl;
  std::cout << std::endl;

  for (auto &&[pos, value] : matrix) {
    for (auto posPart : pos) {
      std::cout << "[" << posPart << "]";
    }
    std::cout << " = " << value << std::endl;
  }

  return 0;
}
