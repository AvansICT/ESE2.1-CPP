#include <iostream>
#include <thread>
#include <vector>
#include <cstring>
#include "log.hpp"
#include "socket.hpp"

#define PORT 8080
#define BUF_SIZE 1024

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
        std::cerr << "Cannot create socket!\n";
        throw std::runtime_error("Cannot create socket");
        return 1;
    }

    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        closeSocket(serverSock);
        std::cerr << "Cannot bind socket\n";
        throw std::runtime_error("Cannot bind socket");
        return 1;
    }

    std::cout << "UDP Server listening on port " << PORT << "...\n";


    char buffer[BUF_SIZE];
    sockaddr_in clientAddr{};
    socklen_t clientLen = sizeof(clientAddr);

    while (true) {
        int bytes = recvfrom(serverSock, buffer, sizeof(buffer) - 1, 0,
            (sockaddr*)&clientAddr, &clientLen);
        if (bytes < 0) break;

        buffer[bytes] = '\0';

        char clientIP[INET_ADDRSTRLEN];
        if (inet_ntop(AF_INET,
            &clientAddr.sin_addr,
            clientIP,
            sizeof(clientIP)) != nullptr) {
            std::cout << "Received from " << clientIP << ": " << buffer << "\n";
        }
        else {
            std::cerr << "inet_ntop() failed\n";
            throw std::runtime_error("inet_ntop() failed");
            break;
        }
        std::cout << "Received from " << clientIP << ": " << buffer << "\n";

        std::string reply = "Server reply: " + std::string(buffer);
        size_t sentBytes = sendto(serverSock, reply.c_str(), (int)reply.size(), 0,
            (sockaddr*)&clientAddr, clientLen);
        if (sentBytes < 0) {
            throw std::runtime_error("Send failed");
        }
    }

    closeSocket(serverSock);

#ifdef _WIN32
    (void)WSACleanup();
#endif

    return 0;
}
