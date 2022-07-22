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
#include <mysql/mysql.h>
#include <sstream>

class Server {
    public:
        Server();
        ~Server();

        int getServerSocket() const;
        int getClientSocket() const;

        void message(std::string msg);
        void startServer();
        void clientConnect();
        void readMessage();
    protected:
    private:
        int _socketServer;
        int _socketClient;
        MYSQL* _dataBase;
};

#endif /* !SERVER_HPP_ */
