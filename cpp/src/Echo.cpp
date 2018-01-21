#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>

#include "Config.hpp"
#include "Echo.hpp"
#include "Trace.hpp"
#include "Utility.hpp"

Echo::Echo()
        : network()
        , client(network)
        , continued(false)
        , stopped(false)
        , sequence(0U)
{
}
bool Echo::contact(
        bool& flagged,
        const std::string& prefix,
        std::string& input,
        std::string& output)
{
    TRACE_PREFIX(prefix);

    std::string host(Config::getHost(prefix));
    int port = Config::getPort(prefix);
    std::string address(Config::address(host, port));

    TRACE_CONNECTING(address);

    client.setBlocking(false);
    client.setConnectTimeout(2.0F);
    client.connect(address);

    client.setReadCallback([&](
            cppsocket::Socket& socket,
            const std::vector<uint8_t>& data) {
        std::ostringstream oss;
        oss << data.data();
        TRACE_READ(socket, oss.str());

        output.assign(oss.str());
        flagged = true;
    });

    client.setConnectCallback([&](
            cppsocket::Socket& socket) {
        TRACE_CONNECTED(socket);

        std::ostringstream oss;
        if (input.size()) {
            oss << input;
        } else {
            STREAM_SOCKET(oss, socket, sequence, Config::ec);
        }
        const std::string& str = oss.str();
        std::vector<uint8_t> vector(str.begin(), str.end());
        vector.push_back(0);

        TRACE_SENDING(socket, str);
        socket.send(vector);
    });

    client.setConnectErrorCallback([&, address](
            cppsocket::Socket& socket) {
        TRACE_CONNECT_ERROR(socket);

        client.connect(address);
    });

    const std::chrono::microseconds sleepTime(10000);
    while (!flagged) {
        network.update();

        std::this_thread::sleep_for(sleepTime);
    }

    return false;
}

bool Echo::run()
{
    std::string forS1;
    std::string fromS1;
    contact(continued, Config::S1_, forS1, fromS1);
    std::string forS2(fromS1);
    std::string fromS2;
    contact(stopped, Config::S2_, forS2, fromS2);

    return false;
}
void Echo::stop() {
    stopped = true;
}
