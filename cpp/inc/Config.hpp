#pragma once

#include <string>

class Config {
private:
    static const std::string _;
    static const std::string PORT;
    static const std::string HOST;
    static const std::string NAME;
public:
    static const std::string S1_;
    static const std::string S2_;
    static const std::string ES_;
    static const std::string EC_;
    static const std::string s1;
    static const std::string s2;
    static const std::string es;
    static const std::string ec;

    static int getPort(const std::string& prefix = _);
    static std::string getHost(const std::string& prefix = _);
    static const std::string& getName(const std::string& nameDefault = ec);

    static std::string address(const std::string& host, int port);
};
