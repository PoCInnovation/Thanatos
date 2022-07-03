/*
** EPITECH PROJECT, 2022
** Thanatos
** File description:
** Server
*/

#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Server {
    public:
        Server();
        ~Server();

        int getServerSocket() const;
        int getClientSocket() const;

        void startServer();
        void clientConnect();
        void readMessage();
    protected:
    private:
        int _socketServer;
        int _socketClient;
};

#endif /* !SERVER_HPP_ */
