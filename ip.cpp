#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "ip.h"

using namespace std;

const uint8_t *IP::getSegments() const {
    return segments;
}

IP::IP(string s) : segments() {
    std::vector<string> strs;
    boost::split(strs, s, boost::is_any_of("."));
    for (int i = 0; i <= 3; i++) {
        this->segments[i] = stoi(strs[i]);
    }
}

bool IP::operator>(const IP &other) const {
    for (int i = 0; i <= 3; i++) {
        if (this->segments[i] == other.segments[i]) {
            continue;
        }
        return this->segments[i] < other.segments[i];
    }
    return false;
}

string IP::toString() const {
    vector<string> segmentStrings;
    for (int i = 0; i <= 3; i++) {
        segmentStrings.push_back(to_string(this->segments[i]));
    }
    return boost::join(segmentStrings, ".");
}

void printFiltered(const vector<const IP *> &IPs, basic_ostream<char> &, const ipMatcher &doesIPMatch) {
    for (auto ip : IPs) {
        auto match = doesIPMatch(*ip);
        if (match) {
            cout << ip->toString() << endl;
        }
    }
}


bool any(const IP &) {
    return true;
}

bool firstIsOne(const IP &ip) {
    return ip.getSegments()[0] == 1;
}

bool first46Second70(const IP &ip) {
    return ip.getSegments()[0] == 46 && ip.getSegments()[1] == 70;
}

bool any46(const IP &ip) {
    auto segments = ip.getSegments();
    for (size_t i = 0; i <= 3; i++) {
        if (segments[i] == 46) {
            return true;
        }
    }
    return false;
}