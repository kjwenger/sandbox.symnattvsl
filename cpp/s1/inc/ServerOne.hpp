#pragma once

#include <vector>

#include <Network.hpp>

#include "Server.hpp"

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
class ServerOne : public Server {
public:
    ServerOne();
};
