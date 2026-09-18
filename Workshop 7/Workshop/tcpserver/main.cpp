#include <iostream>
#include <cstring>
#include "log.hpp"
#include "socket.hpp"

#define PORT 8080
#define BUF_SIZE 1024
const char* message = "Aloha client";
constexpr int BACKLOG = 5;

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "TCP Server!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogTargetOperatingSystem();
    LogTargetCompiler();
#ifdef _WIN32
    WSADATA wsaData;
    (void)WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
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

    std::cout << "TCP Server listening on port " << PORT << "...\n";
    
    if(listen(serverSock, BACKLOG) == SOCKET_ERROR) {
        closeSocket(serverSock);
        std::cerr << "listen error!\n";
        throw std::runtime_error("listen error!");
        return 1;
    }

    SOCKET clientSock = accept(serverSock, nullptr, nullptr);
    if (clientSock == INVALID_SOCKET) {
        std::cerr << "accept error!\n";
        throw std::runtime_error("accept error!");
        return 1;
    }

    char buffer[BUF_SIZE];
    int bytes = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';

    std::cout << "Ontvangen: " << buffer << "\n";

    if (send(clientSock, message, static_cast<int>(strlen(message)), 0) == SOCKET_ERROR) {
        std::cerr << "send error!\n";
        throw std::runtime_error("send error!");
        closeSocket(clientSock);
        closeSocket(serverSock);
        return 1;
    }

    closeSocket(clientSock);
    closeSocket(serverSock);

#ifdef _WIN32
    (void)WSACleanup();
#endif

    return 0;
}
