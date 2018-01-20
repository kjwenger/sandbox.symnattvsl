#pragma once

#include <string>

#include <Network.hpp>

/**
 # 4.1 Phase I
    The new method is divided into three phases.
    In this method,
    the client is known as an echo client and the server is known as an
    echo server because there are a series of packet exchanges between them.
    An echo client communicates with two servers S1 and S2.
    S1 and S2 record the IP address and port number of the echo client,
    and these are then translated by NAT a.
    The following are the steps of the method:
 > F1:
    The echo client communicates with S1.
    Then, S1 analyzes the port number mapped by NAT a.
 > F2:
    S1 conveys the port number to the echo client.
 > F3:
    The echo client sends a packet to S2.
    It includes information obtained on the port number of NAT a
    when the echo client communicated with S1.
    Then, S2 analyzes the port number of NAT a and records it.
    Furthermore, S2 also records the information obtained on the port number
    of NAT a when the echo client communicated with S1 at step F1.
*/
/**
 # 4.2 Phase II
    In phase II, the echo server communicates with S1 and S2
    in a manner similar to that in phase I.
 > F4:
    The echo server communicates with S1.
    Then, S1 analyzes the port number mapped by NAT b.
 > F5:
    S1 conveys the port number to the echo server.
 > F6:
    The echo server sends a packet to S2.
    The packet includes the port number information of NAT b obtained
    from the communication of the echo server with S1 at step F4.
    Then, S2 analyzes the port number of NAT b and records it.
    Furthermore, S2 records the port number information of NAT b obtained
    when the echo server communicated with S1 at step F4.the predicted
    port number and the punching mode to the echo server.
 > F8:
    Based on this information, the echo server sends a large number of packets.
    These packets have a fixed destination port and a low TTL value.
    The echo server binds the port.
    The packets are then sent to the echo client.1
 > F9:
    Using the two kinds of information obtained in phases I and II, namely,
    the communications of NAT b with S1 and S2,
    we can predict a suitable port number for the hole punching.
    S2 sends the information that contains the predicted port number and
    the punching mode to the echo client in a manner similar to that of step F7.
 > F10:
    On the basis of the information obtained in step F9,
    the echo client sends many packets to the echo server.
    These packets have a fixed destination port.
    The echo client binds the port.
    After sending all the packets,
    the echo client switches to the receiving mode.
*/
class EchoClient {
public:
    EchoClient();
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
};
