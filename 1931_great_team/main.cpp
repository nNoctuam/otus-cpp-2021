#include <algorithm>
#include <iostream>
#include <vector>

int main() {
  long teamSize;
  std::cin >> teamSize;

  int maxCompares = 0, maxComparesPosition = 0;
  int previousFlaws = 0, currentFlaws = 0;
  int currentCompares = 0, currentPosition = 0;
  std::cin >> previousFlaws;

  for (int pos = 1; pos < teamSize; pos++) {
    std::cin >> currentFlaws;
    if (currentFlaws < previousFlaws) {
      previousFlaws = currentFlaws;
      currentCompares = 0;
      currentPosition = pos;
    }
    currentCompares++;

    if (currentCompares > maxCompares) {
      maxCompares = currentCompares;
      maxComparesPosition = currentPosition;
    }
  }

  std::cout << (maxComparesPosition + 1) << std::endl;

  return 0;
}