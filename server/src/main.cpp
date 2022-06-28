#include "server.hpp"
#include <unistd.h>
#include <iostream>

int main(void)
{
    int socket_server = start_server();
    int socket_client = 0;

    if (socket_server == -1) {
        return 84;
    }
    while (1) {
        socket_client = connect_server(socket_server);
        if (socket_client == -1) {
            return 84;
        }
        relation_client(socket_client);
        close(socket_client);
    }
    close(socket_server);
    std::cout << "Exit program..." << std::endl;
    return 0;
}
