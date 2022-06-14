#include "http_message.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>

int connect_to_server(const std::string ip, const int port)
{
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        std::cout << "socket creation failed, exit\n";
        exit(0);
    }
    else
        std::cout << "Socket successfully created..\n";
    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ip.c_str());
    servaddr.sin_port = htons(port);

    // connect the client socket to server socket
    std::cout << "Try to connect to " << ip << ":" << port << "..\n";
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        std::cout << "Connection with the server failed, exit\n";
        exit(0);
    }
    else
        std::cout << "Connected to the server\n";
    return sockfd;
}

int main()
{
    auto message = HttpMessage(HttpMessage::HttpMethod::GET, "0.0.0.0",
        "/hello");
    auto socket = connect_to_server("127.0.0.1", 8080);

    message << "Salut je suis le body\n";
    message << "salut";
    message.set_header("cle", "pas cle");
    message.print_message();
    message.send_message(socket);
    close(socket);
}
