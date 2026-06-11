#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include "log.hpp"
#include "socket.hpp"

#define PORT 8080

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "UDP Server!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogTargetOperatingSystem();
    LogTargetCompiler();
#ifdef _WIN32
    WSADATA wsaData;
    (void)WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    SOCKET serverSock = socket(AF_INET, SOCK_DGRAM, 0);
    if (serverSock == INVALID_SOCKET) {
        std::cerr << "Cannot create socket\n";
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Bind failed\n";
        closeSocket(serverSock);
        return 1;
    }

    std::cout << "UDP Server listening on port " << PORT << "...\n";


    char buffer[1024];
    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    while (true) {
        int bytes = recvfrom(serverSock, buffer, sizeof(buffer) - 1, 0,
            (sockaddr*)&clientAddr, &clientLen);
        if (bytes < 0) break;

        buffer[bytes] = '\0';

        char clientIP[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, sizeof(clientIP));
        std::cout << "Received from " << clientIP << ": " << buffer << "\n";

        std::string reply = "Server reply: " + std::string(buffer);
        sendto(serverSock, reply.c_str(), (int)reply.size(), 0,
            (sockaddr*)&clientAddr, clientLen);
    }

    closeSocket(serverSock);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
