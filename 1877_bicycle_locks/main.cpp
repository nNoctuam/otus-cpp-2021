#include <iostream>


int main() {
    int a, b;
    std::cin >> a >> b;

    if (a % 2 == 0 || b % 2 != 0) {
        std::cout << "yes" << std::endl;
    } else {
        std::cout << "no" << std::endl;
    }
    return 0;
}

//
//int detect(int a, int b) {
//    if (a % 2 == 0 || b % 2 == 1) {
//        return 0;
//    } else {
//        return -1;
//    }
//}
//
//int detectCycle(int a, int b) {
//    for (int i = 0; i < 100; i++) {
//        if (i * 2 == a) {
//            return i * 2;
//        }
//        if (i * 2 + 1 == b) {
//            return i * 2 + 1;
//        }
//    }
//    return -1;
//}
//
//int main() {
//    int a, b;
//
//    int d, dc;
//    for (a = 0; a <= 9; a++) {
//        for (b = 0; b <= 9; b++) {
//            d = detect(a, b);
//            dc = detectCycle(a, b);
//            printf("a=%d b=%d | detected=%d | cycle=%d\n", a, b, d, dc);
//            if (d == -1 && dc != -1 || d != -1 && dc == -1) {
//                std::cout << "diff!!!\n" << std::endl;
//            }
//        }
//    }
////    std::cin >> a >> b;
//
////    std::cout << "a=" << a << " b=" << b << std::endl;
//
////    if (a%2 == 0 || b%2 == 1) {
////        std::cout << "yes" << std::endl;
////    } else {
////        std::cout << "no" << std::endl;
////    }
////
////
////    for(int i = 0; i< 500; i++) {
////        if (i*2 == a) {
////            std::cout << "cycle yes a " << i*2 << std::endl;
////            return 0;
////        }
////        if (i*2+1 == b) {
////            std::cout << "cycle yes b " << i*2+1 << std::endl;
////            return 0;
////        }
////    }
////    std::cout << "cycle no" << std::endl;
//
//    return 0;
//}
