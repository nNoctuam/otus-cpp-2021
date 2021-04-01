#pragma once
#include "vector"
#include <iostream>
#include <boost/algorithm/string.hpp>

using namespace std;

class IP {

public:
    const uint8_t *getSegments() const;
    explicit IP(std::string s);
    bool operator>(const IP &other) const;
    std::string toString() const;

private:
    uint8_t segments[4];
};


void sortIPs(vector< const IP*>*);


typedef function<bool(const IP &)> ipMatcher;

void printFiltered(const vector<const IP *> &IPs, basic_ostream<char> &, const ipMatcher &doesIPMatch);

bool any(const IP &);
bool firstIsOne(const IP &);
bool first46Second70(const IP &);
bool any46(const IP &);