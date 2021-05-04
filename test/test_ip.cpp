#define BOOST_TEST_MODULE test_ip

#include <boost/test/unit_test.hpp>
#include "../include/ip.h"

BOOST_AUTO_TEST_SUITE(test_ip)

    BOOST_AUTO_TEST_CASE(test_ip_constructor) {
        auto ip = new IP("127.0.0.1\t25324\t0");
        BOOST_REQUIRE(ip->getSegments()[0] == 127);
        BOOST_REQUIRE(ip->getSegments()[1] == 0);
        BOOST_REQUIRE(ip->getSegments()[2] == 0);
        BOOST_REQUIRE(ip->getSegments()[3] == 1);
    }

    BOOST_AUTO_TEST_CASE(test_ip_toString) {
        auto ip = new IP("127.0.0.1\t25324\t0");
        BOOST_REQUIRE(ip->toString() == "127.0.0.1");
    }


    BOOST_AUTO_TEST_CASE(test_ip_sortIPs) {
        vector<const IP *> ips;
        ips.push_back(new IP("32.0.5.1\t25324\t0"));
        ips.push_back(new IP("127.0.0.1\t25324\t0"));
        ips.push_back(new IP("32.0.0.1\t25324\t0"));
        sortIPs(&ips);
        BOOST_REQUIRE(ips.at(0)->toString() == "127.0.0.1");
        BOOST_REQUIRE(ips.at(1)->toString() == "32.0.5.1");
        BOOST_REQUIRE(ips.at(2)->toString() == "32.0.0.1");
    }


    BOOST_AUTO_TEST_CASE(test_match_any) {
        auto ip = new IP("127.0.0.1\t25324\t0");
        BOOST_REQUIRE(any(*ip));
    }

    BOOST_AUTO_TEST_CASE(test_match_firstIsOne) {
        auto ipGood = new IP("1.0.0.0\t25324\t0");
        auto ipBad = new IP("0.1.1.1\t25324\t0");
        BOOST_REQUIRE(firstIsOne(*ipGood));
        BOOST_REQUIRE_EQUAL(firstIsOne(*ipBad), false);
    }

    BOOST_AUTO_TEST_CASE(test_match_first46Second70) {
        auto ipGood = new IP("46.70.0.1\t25324\t0");
        auto ipBad1 = new IP("46.71.0.1\t25324\t0");
        auto ipBad2 = new IP("45.70.0.1\t25324\t0");
        auto ipBad3 = new IP("0.45.70.1\t25324\t0");
        BOOST_REQUIRE(first46Second70(*ipGood));
        BOOST_REQUIRE_EQUAL(first46Second70(*ipBad1), false);
        BOOST_REQUIRE_EQUAL(first46Second70(*ipBad2), false);
        BOOST_REQUIRE_EQUAL(first46Second70(*ipBad3), false);
    }

    BOOST_AUTO_TEST_CASE(test_match_any46) {
        auto ipGood1 = new IP("46.70.0.1\t25324\t0");
        auto ipGood2 = new IP("45.46.0.1\t25324\t0");
        auto ipGood3 = new IP("45.70.46.1\t25324\t0");
        auto ipGood4 = new IP("0.45.70.46\t25324\t0");
        auto ipBad = new IP("0.45.70.47\t25324\t0");
        BOOST_REQUIRE(any46(*ipGood1));
        BOOST_REQUIRE(any46(*ipGood2));
        BOOST_REQUIRE(any46(*ipGood3));
        BOOST_REQUIRE(any46(*ipGood4));
        BOOST_REQUIRE_EQUAL(any46(*ipBad), false);
    }

}