#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "Config.hpp"
#include "EchoClient.hpp"

EchoClient::EchoClient()
        : network()
        , client(network)
        , continued(false)
        , stopped(false)
{
}
bool EchoClient::contact(
        bool& flagged,
        const std::string& prefix,
        std::string& input,
        std::string& output)
{
    std::cout
            << "-- Prefix: "
            << prefix
            << std::endl;

    std::string host(Config::getHost(prefix));
    int port = Config::getPort(prefix);
    std::string address(Config::address(host, port));

    client.setBlocking(false);
    client.setConnectTimeout(2.0F);
    std::cout
            << "-- Connecting Server: "
            << address
            << std::endl;
    client.connect(address);

    client.setReadCallback([&](
            cppsocket::Socket& socket,
            const std::vector<uint8_t>& data) {
        std::ostringstream oss;
        oss
                << data.data();
        std::cout
                << "-- Read Server: "
                << cppsocket::ipToString(socket.getRemoteIPAddress())
                << std::endl
                << oss.str()
                << std::endl;
        output.assign(oss.str());
        flagged = true;
    });

    client.setConnectCallback([&](
            cppsocket::Socket& socket) {
        std::cout
                << "-- Connected: "
                << cppsocket::ipToString(socket.getRemoteIPAddress())
                << std::endl;
        std::ostringstream oss;
        if (input.size()) {
            oss << input;
        } else {
            oss
                    << ".ec"
                    << std::endl
                    << "Local IP Address:"
                    << cppsocket::ipToString(socket.getLocalIPAddress())
                    << std::endl
                    << "Local Port:"
                    << socket.getLocalPort()
                    << std::endl
                    << "Remote IP Address:"
                    << cppsocket::ipToString(socket.getRemoteIPAddress())
                    << std::endl
                    << "Remote Port:"
                    << socket.getRemotePort()
                    << std::endl;
        }
        const std::string& str = oss.str();
        std::vector<uint8_t> vector(str.begin(), str.end());
        vector.push_back(0);
        std::cout
                << "-- Sending: "
                << str;
        socket.send(vector);
    });

    client.setConnectErrorCallback([&, address](
            cppsocket::Socket& socket) {
        std::cout
                << "-- Connect Error: "
                << cppsocket::ipToString(socket.getRemoteIPAddress())
                << std::endl;

        client.connect(address);
    });

    const std::chrono::microseconds sleepTime(10000);
    while (!flagged) {
        network.update();

        std::this_thread::sleep_for(sleepTime);
    }

    return false;
}

bool EchoClient::run()
{
    std::string forS1;
    std::string fromS1;
    contact(continued, Config::S1_, forS1, fromS1);
    std::string forS2(fromS1);
    std::string fromS2;
    contact(stopped, Config::S2_, forS2, fromS2);

    return false;
}
void EchoClient::stop() {
    stopped = true;
}
