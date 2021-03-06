#include <sstream>
#include <cstdlib>

#include "Config.hpp"

const std::string Config::_("");
const std::string Config::PORT("PORT");
const std::string Config::HOST("HOST");
const std::string Config::NAME("NAME");
const std::string Config::S1_("S1_");
const std::string Config::S2_("S2_");
const std::string Config::ES_("ES_");
const std::string Config::EC_("EC_");
const std::string Config::s1("s1");
const std::string Config::s2("s2");
const std::string Config::es("es");
const std::string Config::ec("ec");

int Config::getPort(const std::string& prefix)
{
    int port(std::getenv((prefix + PORT).c_str())
            ? atoi(std::getenv((prefix + PORT).c_str()))
            : 1337);
    return port;
}
std::string Config::getHost(const std::string& prefix)
{
    std::string host(std::getenv((prefix + HOST).c_str())
            ? std::getenv((prefix + HOST).c_str())
            : "localhost");
    return host;
}
std::string Config::address(const std::string& host, int port)
{
    std::ostringstream oss;
    oss << host;
    oss << ":";
    oss << port;
    return oss.str();
}
const std::string& Config::getName(const std::string& nameDefault)
{
    static std::string name(std::getenv(NAME.c_str())
             ? std::getenv(NAME.c_str())
             : "name");
    return name;
}
