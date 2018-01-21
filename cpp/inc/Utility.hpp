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

#define MATCH_ECHO_CLIENT_MESSAGE(oss, messages) \
{ \
    std::istringstream iss(oss.str()); \
    std::string first; \
    std::getline(iss, first); \
    messages[first] = oss.str(); \
    std::string ec(first); \
    std::string _es(".es"); \
    auto found = ec.find(_es); \
    if (found != std::string::npos) { \
        ec.replace(found, _es.length(), ".ec"); \
        if (ec != first) { \
            auto iterator = messages.find(ec); \
            if (iterator != messages.end()) \
            { \
                oss << iterator->second; \
            } \
        } \
    } \
} \

#define REMOVE_CLIENT(clients, client) \
for (auto \
        iterator = clients.begin(); \
        iterator != clients.end();) \
{ \
    auto& at = *iterator; \
    bool identical = (&at == &client); \
    if (identical) \
    { \
        clients.erase(iterator); \
        break; \
    } \
    else \
    { \
        ++iterator; \
    } \
} \

