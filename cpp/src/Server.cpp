#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "Config.hpp"
#include "Server.hpp"

Server::Server()
        : network()
        , server(network)
        , clients()
        , stopped(false)
{
}
bool Server::run()
{
    const std::chrono::microseconds sleepTime(10000);
    int port = Config::getPort();

    server.setBlocking(false);
    server.startAccept(cppsocket::ANY_ADDRESS, port);

    server.setAcceptCallback([&](
            cppsocket::Socket&,
            cppsocket::Socket& client) {
        std::cout
                << "Client Connected: "
                << cppsocket::ipToString(client.getRemoteIPAddress())
                << std::endl;

        client.setReadCallback([&](
                cppsocket::Socket& socket,
                const std::vector<uint8_t>& data) {
            std::ostringstream oss;
            oss
                    << data.data()
                    << std::endl;
            std::cout
                    << "Read Client: "
                    << cppsocket::ipToString(socket.getRemoteIPAddress())
                    << std::endl
                    << oss.str()
                    << std::endl;
            oss
                    << "."
                    << Config::getName()
                    << std::endl
                    << "Local IP Address:"
                    << cppsocket::ipToString(client.getLocalIPAddress())
                    << std::endl
                    << "Local Port:"
                    << client.getLocalPort()
                    << std::endl
                    << "Remote IP Address:"
                    << cppsocket::ipToString(client.getRemoteIPAddress())
                    << std::endl
                    << "Remote Port:"
                    << client.getRemotePort()
                    << std::endl;
            const std::string& str = oss.str();
            std::vector<uint8_t> vector(str.begin(), str.end());
            std::this_thread::sleep_for(sleepTime);
            std::cout
                    << "Sending: "
                    << cppsocket::ipToString(client.getRemoteIPAddress())
                    << std::endl
                    << str
                    << std::endl;
            socket.send(vector);
        });

        client.startRead();

        client.setCloseCallback([&](
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
        clients.push_back(std::move(client));
    });

    while (!stopped) {
        network.update();

        std::this_thread::sleep_for(sleepTime);
    }

    return false;
}
void Server::stop() {
    stopped = true;
}
