#include "server.hpp"
#include "Server.hpp"
#include <unistd.h>
#include <iostream>

int main(void)
{
    Server server;
    server.startServer();

    if (server.getServerSocket() == -1)
        return 84;
    while (1) {
        server.clientConnect();
        if (server.getClientSocket() == -1)
            return 84;
        server.readMessage();
    }
    std::cout << "Exit program..." << std::endl;
    return 0;
}
