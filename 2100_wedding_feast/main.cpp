#include <iostream>

int main() {
  int n;
  std::cin >> n;
  std::string guest;
  int seats = 2 + n;
  while (n-- + 1) {
    std::getline(std::cin, guest);
    if (guest.find('+') != std::string::npos) {
      seats++;
    }
  }
  if (seats == 13) {
    seats++;
  }
  std::cout << seats * 100 << std::endl;

  return 0;
}