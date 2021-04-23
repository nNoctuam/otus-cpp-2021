#include <iostream>

int main() {
    int speed, minutes;

    std::cin >> speed >> minutes;

    int carsInMinute, carsLeft = 0;
    for (int i=0; i<minutes; i++) {
        std::cin >> carsInMinute;
        carsLeft += carsInMinute - speed;
        if (carsLeft < 0) {
            carsLeft = 0;
        }
    }

    std::cout << carsLeft << std::endl;

    return 0;
}
