#pragma once

#define STREAM_SOCKET(os, socket, sequence, nameDefault) \
oss \
    << "." \
    << Config::getName(nameDefault) \
    << ":" \
    << ++sequence \
    << std::endl \
    << "la:" \
    << cppsocket::ipToString(socket.getLocalIPAddress()) \
    << std::endl \
    << "lp:" \
    << socket.getLocalPort() \
    << std::endl \
    << "ra:" \
    << cppsocket::ipToString(socket.getRemoteIPAddress()) \
    << std::endl \
    << "rp:" \
    << socket.getRemotePort() \
    << std::endl \

