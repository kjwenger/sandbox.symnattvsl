#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "Config.hpp"
#include "ServerTwo.hpp"

ServerTwo::ServerTwo()
        : network()
        , server(network)
        , clients()
        , stopped(false)
{
}
bool ServerTwo::f1()
{
    int port = Config::getPort(Config::S1_);

    server.setBlocking(false);
    server.startAccept(cppsocket::ANY_ADDRESS, port);

    server.setAcceptCallback([&](
            cppsocket::Socket& s,
            cppsocket::Socket& c) {
        std::cout
                << "Client Connected:"
                << std::endl;
        c.startRead();
        std::ostringstream oss;
        oss
                << ".s2"
                << std::endl
                << "Local IP Address:"
                << cppsocket::ipToString(c.getLocalIPAddress())
                << std::endl
                << "Local Port:"
                << c.getLocalPort()
                << std::endl
                << "Remote IP Address:"
                << cppsocket::ipToString(c.getRemoteIPAddress())
                << std::endl
                << "Remote Port:"
                << c.getRemotePort()
                << std::endl;
        const std::string& str = oss.str();
        std::vector<uint8_t> vector(str.begin(), str.end());
        c.send(vector);
        c.setCloseCallback([&](
                cppsocket::Socket& socket) {
            std::cout
                    << "Client Disconnected: "
                    << cppsocket::ipToString(socket.getRemoteIPAddress())
                    << std::endl;

            for (auto
                 iterator = clients.begin();
                 iterator != clients.end();)
            {
                if (&(*iterator) == &socket)
                {
                    iterator = clients.erase(iterator);
                    break;
                }
                else
                {
                    ++iterator;
                }
            }

        });
        clients.push_back(std::move(c));
    });

    const std::chrono::microseconds sleepTime(10000);
    while (!stopped) {
        network.update();

        std::this_thread::sleep_for(sleepTime);
    }

    return false;
}
bool ServerTwo::f2()
{
    return false;
}
bool ServerTwo::f3()
{
    return false;
}
void ServerTwo::stop() {
    stopped = true;
}
