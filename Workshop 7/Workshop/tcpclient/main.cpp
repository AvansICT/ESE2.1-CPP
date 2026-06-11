#include <iostream>
#include <cstring>
#include "log.hpp"
#include "socket.hpp"

#define PORT 8080
#define IP_ADDRESS "127.0.0.1"  //localhost loopback address

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
    if (sock == INVALID_SOCKET) { std::cerr << "Fout bij socket!\n"; return 1; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    inet_pton(AF_INET, IP_ADDRESS, &addr.sin_addr);

    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Fout bij connect!\n"; return 1;
    }

    send(sock, "Hallo server", 12, 0);

    char buffer[1024];
    int bytes = recv(sock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';
    std::cout << "Ontvangen van server: " << buffer << "\n";

    closeSocket(sock);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
