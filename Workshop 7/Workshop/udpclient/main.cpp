#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>
#include "log.hpp"
#include "socket.hpp"

#define PORT 8080
#define BUF_SIZE 1024
#define IP_ADDRESS "127.0.0.1"  //localhost loopback address

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "UDP CLient!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogTargetOperatingSystem();
    LogTargetCompiler();

#ifdef _WIN32
    WSADATA wsaData;
    (void)WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Cannot create socket\n";
        throw std::runtime_error("Cannot create socket");
        return 1;
    }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    int result = inet_pton(AF_INET, IP_ADDRESS, &addr.sin_addr);
    if (result <= 0) {
        std::cerr << "Invalid address\n";
        throw std::runtime_error("Invalid address");
        return 1;
    }

    while (true) {
        std::string msg;
        std::cout << "Enter message (or 'quit'): ";
        std::getline(std::cin, msg);
        if (msg == "quit") break;

        size_t sentBytes = sendto(sock, msg.c_str(), (int)msg.size(), 0,
            (sockaddr*)&addr, sizeof(addr));
        if (sentBytes < 0) {
            throw std::runtime_error("Send failed");
        }
        char buffer[BUF_SIZE];
        sockaddr_in fromAddr{};
        socklen_t fromLen = sizeof(fromAddr);
        int bytes = recvfrom(sock, buffer, sizeof(buffer) - 1, 0,
            (sockaddr*)&fromAddr, &fromLen);
        if (bytes > 0) {
            buffer[bytes] = '\0';
            std::cout << "Server says: " << buffer << "\n";
        }
    }

    closeSocket(sock);

#ifdef _WIN32
    (void)WSACleanup();
#endif

    return 0;
}
