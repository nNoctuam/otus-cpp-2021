#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "../include/ip.h"

int main() {
    std::vector<std::unique_ptr<const IP>> ips;
    std::string row;
    std::vector<std::string> rowSegments;

    while (getline(std::cin, row)) {
        boost::split(rowSegments, row, boost::is_any_of("\t"));
        ips.push_back(std::make_unique<IP>(rowSegments[0]));
    }

    sortIPs(ips);

    printFiltered(ips, std::cout, any);
    printFiltered(ips, std::cout, firstIsOne);
    printFiltered(ips, std::cout, first46Second70);
    printFiltered(ips, std::cout, any46);

    return 0;
}
