#include <iostream>

int main() {
    int a1, a2, a3, b1, b2, b3;
    int basket1, basket2, berries1, berries2;
    std::cin >> a1 >> b1 >> a2 >> b2 >> a3 >> b3;

    basket1 = a3;
    basket2 = b2;

    berries1 = a1 - basket1;
    berries2 = b1 - basket2;

    std::cout << berries1 << " " << berries2 << std::endl;

    return 0;
}
