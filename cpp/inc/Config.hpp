#pragma once

#include <string>

class Config {
private:
    static const std::string _;
    static const std::string PORT;
    static const std::string HOST;
public:
    static const std::string S1_;
    static const std::string S2_;
    static const std::string ES_;

    static int getPort(const std::string& prefix = _);
    static const std::string& getHost(const std::string& prefix = _);

    static std::string address(const std::string& host, int port);
};
