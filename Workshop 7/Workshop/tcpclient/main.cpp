#include <iostream>
#include <cstring>
#include <stdexcept>
#include "log.hpp"
#include "socket.hpp"

#define PORT 8080
#define BUF_SIZE 1024
#define IP_ADDRESS "127.0.0.1"  //localhost loopback address
const char* message = "Aloha server";

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "TCP Client!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogTargetOperatingSystem();
    LogTargetCompiler();

#ifdef _WIN32
    WSADATA wsaData;
    (void)WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
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
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        throw std::runtime_error("connect failed");
        std::cerr << "connect failed\n"; 
        return 1;
    }

    if (send(sock, message, static_cast<int>(strlen(message)), 0) == SOCKET_ERROR) {
        std::cerr << "send error!\n";
        throw std::runtime_error("send error!");
        closeSocket(sock);
        return 1;
    }
 
    char buffer[BUF_SIZE];
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';
    std::cout << "Ontvangen van server: " << buffer << "\n";

    closeSocket(sock);

#ifdef _WIN32
    (void)WSACleanup();
#endif

    return 0;
}
