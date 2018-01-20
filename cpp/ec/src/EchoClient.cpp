#include <iostream>
#include <chrono>
#include <thread>

#include "Config.hpp"
#include "EchoClient.hpp"

EchoClient::EchoClient()
        : network()
        , client(network)
        , stopped(false)
{
}
bool EchoClient::f1()
{
    std::string host(Config::getHost(Config::S1_));
    int port = Config::getPort(Config::S1_);
    std::string address(Config::address(host, port));

    client.setBlocking(false);
    client.setConnectTimeout(2.0F);
    client.connect(address);

    client.setReadCallback([](
            cppsocket::Socket& socket,
            const std::vector<uint8_t>& data) {
        std::cout
                << "Read: "
                << data.data()
                << " from "
                << cppsocket::ipToString(socket.getRemoteIPAddress())
                << std::endl;
    });

    client.setConnectCallback([](
            cppsocket::Socket& socket) {
        std::cout
                << "Connected: "
                << cppsocket::ipToString(socket.getRemoteIPAddress())
                << std::endl;
        socket.send({'t', 'e', 's', 't', '\0'});
    });

    client.setConnectErrorCallback([&, address](
            cppsocket::Socket& socket) {
        std::cout
                << "Connect Error: "
                << cppsocket::ipToString(socket.getRemoteIPAddress())
                << std::endl;

        client.connect(address);
    });

    const std::chrono::microseconds sleepTime(10000);
    while (!stopped) {
        network.update();

        std::this_thread::sleep_for(sleepTime);
    }

    return false;
}
bool EchoClient::f2()
{
    return false;
}
bool EchoClient::f3()
{
    return false;
}
void EchoClient::stop() {
    stopped = true;
}
