/*
** EPITECH PROJECT, 2022
** Thanatos
** File description:
** Server
*/

#include "Server.hpp"

Server::Server()
{
    _socketClient = -1;
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);
}

Server::~Server()
{
    close(_socketServer);
    //close(_socketClient);
}

int Server::getServerSocket() const
{
    return _socketServer;
}

int Server::getClientSocket() const
{
    return _socketClient;
}

void Server::startServer()
{
    struct sockaddr_in myaddr;
    int listenPort = 4000;
    struct linger linger_opt = {1, 0};

    if (_socketServer == -1) {
        std::cerr << "Setup Fail..." << std::endl;
        return;
    }
    std::cout << "Socket successfully created..." << std::endl;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(listenPort);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    setsockopt(_socketServer, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));
    bind(_socketServer, (struct sockaddr*) &myaddr, sizeof(myaddr));
    listen(_socketServer, 1);
}

void Server::clientConnect()
{
    struct sockaddr_in peeraddr;
    socklen_t peeraddr_len;

    std::cout << "Wait new client..." << std::endl;
    _socketClient = accept(_socketServer, (struct sockaddr*) &peeraddr, &peeraddr_len);
    if (_socketClient != -1)
        std::cout << "Connected..." << std::endl;
    else
        std::cerr << "Connexion Fail..." << std::endl;
}

void Server::readMessage()
{
    char buffer[4096];
    char *split;

    if (read(_socketClient, buffer, 4096) == -1) {
        std::cout << "Error" << std::endl;
        return;
    }
    printf("|%s|\n", buffer);
    split = strtok(buffer, "\r\n");
    while (split != NULL) {
        split = strtok(NULL, "\r\n");
        // printf("|%s|\n", split);
    }
    close(_socketClient);
}