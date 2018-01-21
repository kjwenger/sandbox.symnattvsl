#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "Config.hpp"
#include "Utility.hpp"
#include "Server.hpp"
#include "Trace.hpp"

Server::Server()
        : network()
        , server(network)
        , clients()
        , stopped(false)
        , sequence(0U)
        , messages()
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
        TRACE_CONNECTED(client);

        client.setReadCallback([&](
                cppsocket::Socket& socket,
                const std::vector<uint8_t>& data) {
            std::ostringstream oss;
            oss << data.data();
            TRACE_READ(socket, oss.str());

            //Find a matching ".ec:<sequence>" for a possible ".es:<sequence>"
            std::istringstream iss(oss.str());
            std::string first;
            std::getline(iss, first); //Extract a possible ".es:<sequence>"
            std::string ec(first);
            std::string es(".es");
            unsigned long found = ec.find(es);
            ec.replace(found, es.length(), ".ec"); //Convert to a possible matching ".ec:<sequence>"
            if (ec != first) { //It was an ".es:<sequence>" to begin with
                auto iterator = messages.find(ec); //Find a previous matching message from the echo client
                if (iterator != messages.end())
                {
                    //Matching ".ec:<sequence>" found for ".es:<sequence>", add to send message
                    oss << iterator->second;
                }
            }
            messages[first] = oss.str();

            STREAM_SOCKET(oss, socket, sequence, Config::s1);
            const std::string& str = oss.str();
            std::vector<uint8_t> vector(str.begin(), str.end());
            vector.push_back(0);
            std::this_thread::sleep_for(sleepTime);

            TRACE_SENDING(socket, str);
            socket.send(vector);
        });

        client.startRead();

        client.setCloseCallback([&](
                cppsocket::Socket& socket) {
            TRACE_DISCONNECTED(socket);

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
