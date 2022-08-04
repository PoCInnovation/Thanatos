#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <mysql/mysql.h>
#include <sstream>
#include <fstream>
#include <bits/stdc++.h>

enum Cycles {
    DB = 0,
    fileName = 1,
    fileContent = 2
};

class Server {
    public:
        Server();
        ~Server();

        int getServerSocket() const;
        int getClientSocket() const;

        void message(std::string msg);
        void startServer();
        void clientConnect();
        std::string readResponceIntoString();
        void interpretMessage();
    protected:
    private:
        int _socketServer;
        int _socketClient;
        MYSQL* _dataBase;
};

#endif /* !SERVER_HPP_ */
