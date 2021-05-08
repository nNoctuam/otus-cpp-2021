#include <iostream>
#include <map>

int main() {
  std::map<long, short> numbers;

  for (int teamMember=0; teamMember < 3; teamMember++) {
    int count;
    long number;
    std::cin >> count;
    while (count--) {
      std::cin >> number;
      if (numbers.count(number) == 0) {
        numbers.emplace(number, 1);
      } else {
          numbers.at(number)++;
      }
    }
  }

  int ownNumbersCount = 0;
  for (auto k : numbers) {
    if (k.second == 3) {
      ownNumbersCount++;
    }
  }

  std::cout << ownNumbersCount << std::endl;

  return 0;
}