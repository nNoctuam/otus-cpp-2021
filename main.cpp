#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "ip.h"

using namespace std;

int main() {
    vector<const IP *> ips;
    string row;
    vector<string> lineSegments;

    while (getline(cin, row)) {
        boost::split(lineSegments, row, boost::is_any_of("\t"));
        ips.push_back(new IP(lineSegments[0]));
    }

    sort(ips.rbegin(), ips.rend(), [](const IP *a, const IP *b) { return *a > *b; });

    printFiltered(ips, cout, any);
    printFiltered(ips, cout, firstIsOne);
    printFiltered(ips, cout, first46Second70);
    printFiltered(ips, cout, any46);

    return 0;
}
