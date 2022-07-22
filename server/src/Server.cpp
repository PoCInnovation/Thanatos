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

    _dataBase = mysql_init(NULL);
    if(!_dataBase)
        std::cerr << "MySQL initialization failed! " << std::endl;
    _dataBase = mysql_real_connect(_dataBase, "localhost", "root", "passwd123",
        "poc", 0, NULL, 0);
    if(!_dataBase)
        std::cerr << "Connection Error! " << std::endl;
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

void Server::message(std::string msg)
{
   std::cout << msg << std::endl;
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

// void Server::printAllVictims()
// {
//    MYSQL_RES* rset;
//    MYSQL_ROW rows;
//    string sql = "SELECT * FROM victims";
//    if(mysql_query(db_conn, sql.c_str())) {
//       message("Error printing all accounts! ");
//       return;
//    }

//    rset = mysql_use_result(db_conn);

//    cout << left << setw(10) << setfill('-') << left << '+'
//         << setw(21) << setfill('-') << left << '+'
//         << setw(21)
//         << setfill('-') << left << '+' << setw(21)
//         << setfill('-')
//         << '+' << '+' << endl;
//    cout << setfill(' ') << '|' << left << setw(9)
//         << "Account"
//         << setfill(' ') << '|' << setw(20) << "First Name"
//         << setfill(' ') << '|' << setw(20) << "Last Name"
//         << setfill(' ') << '|' << right << setw(20)
//         << "Balance" << '|' << endl;

//    cout << left << setw(10) << setfill('-') << left
//        << '+' << setw(21) << setfill('-') << left << '+'
//        << setw(21)
//        << setfill('-') << left << '+' << setw(21) << setfill('-')
//        << '+' << '+' << endl;
//    if(rset) {
//       while((rows = mysql_fetch_row(rset))) {
//          cout << setfill(' ') << '|' << left << setw(9) << rows[0]
//               << setfill(' ') << '|' << setw(20) << rows[1]
//               << setfill(' ') << '|' << setw(20) << rows[2]
//               << setfill(' ') << '|' << right << setw(20)
//               << rows[3] << '|' << endl;
//       }
//       cout << left << setw(10) << setfill('-') << left
//            << '+' << setw(21) << setfill('-') << left << '+'
//            << setw(21)
//            << setfill('-') << left << '+' << setw(21)
//            << setfill('-')
//            << '+' << '+' << endl;
//    }
//    mysql_free_result(rset);
// }

// void Server::createVictim(BankAccount* ba)
// {
//    stringstream ss;
//    ss << "INSERT INTO bank_account(acc_no, fname, lname,
//          balance)"
//       << "values (" << ba->getAccountNumber() << ", '"
//          << ba->getFirstName() + "','"
//          << ba->getLastName() << "',"
//          << ba->getBalance() << ")";
//    if(mysql_query(db_conn, ss.str().c_str()))
//       message("Failed to create account! ");
//    else
//       message("Account creation successful.");
// }