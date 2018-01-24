#pragma once

#include <vector>
#include <map>

#include <Network.hpp>

class Server {
public:
    Server();
    bool run();
    void stop();
private:
    cppsocket::Network network;
    cppsocket::Socket server;
    std::vector<cppsocket::Socket> clients;
    bool stopped;
    unsigned int sequence;
    std::map<std::string, std::string> messages;
};
