#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

class IP {

public:
    uint segments[4];

    explicit IP(string s): segments() {
        std::vector<string> strs;
        boost::split(strs, s, boost::is_any_of("."));
        for (int i = 0; i <= 3; i++) {
            this->segments[i] = stoi(strs[i]);
        }
    }

    bool operator>(const IP &other) const {
        for (int i = 0; i <= 3; i++) {
            if (this->segments[i] == other.segments[i]) {
                continue;
            }
            return this->segments[i] < other.segments[i];
        }
        return false;
    }

    string toString() const {
        vector<string> segmentStrings;
        for (int i = 0; i <= 3; i++) {
            segmentStrings.push_back(to_string(this->segments[i]));
        }
        return boost::join(segmentStrings, ".");
    }

private:

};


typedef function<bool(const IP &)> ipMatcher;

void printFiltered(const vector<const IP *> &IPs, basic_ostream<char> &, const ipMatcher &doesIPMatch) {
    for (auto ip : IPs) {
        auto match = doesIPMatch(*ip);
        if (match) {
            cout << ip->toString() << endl;
        }
    }
}

int main() {
    vector<const IP *> ips;
    string row;
    vector<string> lineSegments;

    while (getline(cin, row)) {
        boost::split(lineSegments, row, boost::is_any_of("\t"));
        ips.push_back(new IP(lineSegments[0]));
    }

    sort(ips.rbegin(), ips.rend(), [](const IP *a, const IP *b) { return *a > *b; });

    const ipMatcher any = [](const IP &) -> bool {
        return true;
    };
    const ipMatcher firstIsOne = [](const IP &ip) -> bool {
        return ip.segments[0] == 1;
    };
    const ipMatcher first46Second70 = [](const IP &ip) -> bool {
        return ip.segments[0] == 46 && ip.segments[1] == 70;
    };
    const ipMatcher any46 = [](const IP &ip) -> bool {
        for (size_t i = 0; i <= 3; i++) {
            if (ip.segments[i] == 46) {
                return true;
            }
        }
        return false;
    };

    printFiltered(ips, cout, any);
    printFiltered(ips, cout, firstIsOne);
    printFiltered(ips, cout, first46Second70);
    printFiltered(ips, cout, any46);

    return 0;
}
