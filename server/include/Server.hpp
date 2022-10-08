#ifndef SERVER_HPP_
#define SERVER_HPP_

#include <iostream>
#include <mysql/mysql.h>

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
        int startServer();
        int clientConnect();
        std::string readResponceIntoString();
        void interpretMessage();
        void manageClient(int clientSocket);
    protected:
    private:
        int _socketServer;
        MYSQL* _dataBase;
};

#endif /* !SERVER_HPP_ */
