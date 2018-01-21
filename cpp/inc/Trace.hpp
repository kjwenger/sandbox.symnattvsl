#pragma once

#define TRACE_PREFIX(prefix) \
std::cout \
    << "-- Prefix: " \
    << prefix \
    << std::endl \

#define TRACE_CONNECTING(address) \
std::cout \
    << "-- Connecting: " \
    << address \
    << std::endl \

#define TRACE_READ(socket, str) \
std::cout \
    << "-- Read: " \
    << cppsocket::ipToString(socket.getRemoteIPAddress()) \
    << std::endl \
    << str \
    << std::endl \

#define TRACE_CONNECTED(socket) \
std::cout \
    << "-- Connected: " \
    << cppsocket::ipToString(socket.getRemoteIPAddress()) \
    << std::endl \

#define TRACE_SENDING(socket, str) \
std::cout \
    << "-- Sending: " \
    << cppsocket::ipToString(socket.getRemoteIPAddress()) \
    << std::endl \
    << str \
    << std::endl \

#define TRACE_CONNECT_ERROR(socket) \
std::cout \
    << "-- Connect Error: " \
    << cppsocket::ipToString(socket.getRemoteIPAddress()) \
    << std::endl \

#define TRACE_DISCONNECTED(socket) \
std::cout \
    << "-- Disconnected: " \
    << cppsocket::ipToString(socket.getRemoteIPAddress()) \
    << std::endl \

