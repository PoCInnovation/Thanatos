#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>

int connect_server(int socket_server)
{
    struct sockaddr_in peeraddr;
    socklen_t peeraddr_len;
    int socket_client = 0;

    std::cout << "Wait new client..." << std::endl;
    socket_client = accept(socket_server, (struct sockaddr*) &peeraddr, &peeraddr_len);
    if (socket_client == -1) {
        std::cerr << "Connexion Fail..." << std::endl;
        return -1;
    }
    std::cout << "Connected..." << std::endl;
    return socket_client;
}

int start_server(void)
{
    int socket_server = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in myaddr;
    int listenPort = 4000;
    struct linger linger_opt = {1, 0};

    if (socket_server == -1) {
        std::cerr << "Setup Fail..." << std::endl;
        return -1;
    }
    std::cout << "Socket successfully created..." << std::endl;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(listenPort);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    setsockopt(socket_server, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));
    bind(socket_server, (struct sockaddr*) &myaddr, sizeof(myaddr));
    listen(socket_server, 1);
    return socket_server;
}
