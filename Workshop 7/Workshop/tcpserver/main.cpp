#include <iostream>
#include <cstring>
#include "log.hpp"
#include "socket.hpp"

#define PORT 8080

int main([[maybe_unused]] int argc, [[maybe_unused]] char* argv[]) {
    std::cout << "TCP Server!\n";
    std::cout << __DATE__ << " " << __TIME__ << std::endl; // log date and time of compilation, not runtime
    LogOperatingSystem();
    LogCompiler();
#ifdef _WIN32
    WSADATA wsaData;
    (void)WSAStartup(MAKEWORD(2, 2), &wsaData);
#endif

    SOCKET serverSock = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSock == INVALID_SOCKET) { std::cerr << "Fout bij socket!\n"; return 1; }

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(serverSock, (sockaddr*)&addr, sizeof(addr)) == SOCKET_ERROR) {
        std::cerr << "Fout bij bind!\n"; return 1;
    }

    listen(serverSock, 5);
    std::cout << "Server luistert op poort " << PORT << "...\n";

    SOCKET clientSock = accept(serverSock, nullptr, nullptr);
    if (clientSock == INVALID_SOCKET) { std::cerr << "Fout bij accept!\n"; return 1; }

    char buffer[1024];
    int bytes = recv(clientSock, buffer, sizeof(buffer) - 1, 0);
    buffer[bytes] = '\0';

    std::cout << "Ontvangen: " << buffer << "\n";

    send(clientSock, "Hallo client", 12, 0);

    closeSocket(clientSock);
    closeSocket(serverSock);

#ifdef _WIN32
    WSACleanup();
#endif

    return 0;
}
