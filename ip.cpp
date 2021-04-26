#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "ip.h"

using namespace std;

const std::array<uint8_t, IP::SEGMENTS_COUNT> IP::getSegments() const {
    return segments;
}

IP::IP(const string &s) : segments() {
    std::vector<string> strs;
    strs.reserve(IP::SEGMENTS_COUNT);
    boost::split(strs, s, boost::is_any_of("."));
    for (int i = 0; i < IP::SEGMENTS_COUNT; i++) {
        this->segments[i] = stoi(strs[i]);
    }
}

bool IP::operator>(const IP &other) const {
    return this->segments > other.segments;
}

string IP::toString() const {
    vector<string> segmentStrings;
    segmentStrings.reserve(IP::SEGMENTS_COUNT);
    for (int i = 0; i < IP::SEGMENTS_COUNT; i++) {
        segmentStrings.push_back(to_string(this->segments[i]));
    }
    return boost::join(segmentStrings, ".");
}


void sortIPs(vector<const IP *> *ips) {
    sort(ips->begin(), ips->end(), [](const IP *a, const IP *b) { return *a > *b; });
}


void printFiltered(const vector<const IP *> &IPs, basic_ostream<char> &output, const ipMatcher &doesIPMatch) {
    for (const auto &ip : IPs) {
        if (doesIPMatch(*ip)) {
            output << ip->toString() << endl;
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
    for (size_t i = 0; i < IP::SEGMENTS_COUNT; i++) {
        if (segments[i] == 46) {
            return true;
        }
    }
    return false;
}