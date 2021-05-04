#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>
#include "../include/ip.h"


const std::array<uint8_t, IP::SEGMENTS_COUNT> &IP::getSegments() const {
    return segments;
}

IP::IP(const std::string &s) : segments() {
    std::vector<std::string> strs;
    strs.reserve(IP::SEGMENTS_COUNT);
    boost::split(strs, s, boost::is_any_of("."));
    for (int i = 0; i < IP::SEGMENTS_COUNT; i++) {
        this->segments[i] = stoi(strs[i]);
    }
}

bool IP::operator>(const IP &other) const {
    return this->segments > other.segments;
}

std::string IP::toString() const {
    std::vector<std::string> segmentStrings;
    segmentStrings.reserve(IP::SEGMENTS_COUNT);
    for (int i = 0; i < IP::SEGMENTS_COUNT; i++) {
        segmentStrings.push_back(std::to_string(this->segments[i]));
    }
    return boost::join(segmentStrings, ".");
}


void sortIPs(std::vector<std::unique_ptr<const IP>> &IPs) {
    sort(IPs.begin(), IPs.end(), [](const std::unique_ptr<const IP> &a, const std::unique_ptr<const IP> &b) { return *a > *b; });
}


void printFiltered(
        const std::vector<std::unique_ptr<const IP>> &IPs,
        std::basic_ostream<char> &output,
        const ipMatcher &doesIPMatch
) {
    for (const auto &ip : IPs) {
        if (doesIPMatch(*ip)) {
            output << ip->toString() << std::endl;
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