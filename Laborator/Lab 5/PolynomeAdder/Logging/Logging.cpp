// Logging.cpp : Defines the functions for the static library.
//

#include "framework.h"
#include "Logging.h"

#include <WinSock2.h>
#include <exception>
#include <string>
#include <iostream>
#include <cstring>

#define DEFAULT_PORT 40000
#define LOCALHOST 0x7F000001  // hex representation of 127.0.0.1

// TODO: This is an example of a library function
void SendLog(double Time)
{

    int retVal = 0;
    SOCKET s = INVALID_SOCKET;

    WSADATA wsaData;

    retVal = WSAStartup(MAKEWORD(2, 2), &wsaData);
    char msg[100];
    if (retVal)
    {
        sprintf_s(
            msg,
            "WinSock2 failed to start with error 0x%08X. WSAGetLastError returned %d.",
            retVal,
            WSAGetLastError());

        throw std::exception(msg);
    }

    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == INVALID_SOCKET)
    {
        sprintf_s(
            msg,
            "Socket initialization failure. WSAGetLastError returned %d.",
            WSAGetLastError());

        WSACleanup();
        throw std::exception(msg);
    }

    sockaddr_in sAddr;
    ZeroMemory(&sAddr, sizeof(sockaddr_in));
    sAddr.sin_family = AF_INET;
    sAddr.sin_port = htons(DEFAULT_PORT);
    sAddr.sin_addr.s_addr = htonl(LOCALHOST);

    // TODO fix connection refusal
    retVal = connect(s, (const sockaddr*)&sAddr, sizeof(sockaddr_in));
    if (retVal)
    {
        sprintf_s(
            msg,
            "Failed to connect to host. WSAGetLastError returned %d.",
            WSAGetLastError());

        closesocket(s);
        WSACleanup();
        throw std::exception(msg);
    }

    char buf[70];
    sprintf_s(buf, "Time %f", Time);

    retVal = send(s, buf, strlen(buf), 0);
    if (retVal == SOCKET_ERROR)
    {
        sprintf_s(
            msg,
            "Failed to send data to host. WSAGetLastError returned %d.",
            WSAGetLastError());
        closesocket(s);
        WSACleanup();

        throw std::exception(msg);
    }

    closesocket(s);
    WSACleanup();
}
