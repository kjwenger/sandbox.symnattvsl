#pragma once

#include <string>

#include <Network.hpp>

class Echo {
public:
    Echo();
    bool run();
    bool contact(
            bool& flagged,
            const std::string& prefix,
            std::string& input,
            std::string& output);
    void stop();
private:
    cppsocket::Network network;
    cppsocket::Socket client;
    bool continued;
    bool stopped;
    unsigned int sequence;
};
