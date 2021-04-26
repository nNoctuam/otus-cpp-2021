#pragma once

#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

class IP {

public:
    const static int SEGMENTS_COUNT = 4;

    std::array<uint8_t, SEGMENTS_COUNT> getSegments() const;

    explicit IP(const std::string &s);

    bool operator>(const IP &other) const;

    std::string toString() const;

private:
    std::array<uint8_t, SEGMENTS_COUNT> segments;
};


void sortIPs(vector<const IP *> *);


typedef function<bool(const IP &)> ipMatcher;

void printFiltered(const vector<const IP *> &IPs, basic_ostream<char> &, const ipMatcher &doesIPMatch);

bool any(const IP &);

bool firstIsOne(const IP &);

bool first46Second70(const IP &);

bool any46(const IP &);