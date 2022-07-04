#include "http_res.hpp"
#include "http_req.hpp"
#include "manage_messages.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <strings.h>
#include <unistd.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <cstring>
#include <fstream>
#include <string>

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

char *get_ip_addr(void)
{
    ifaddrs *ip = NULL;

    getifaddrs(&ip);
    for (; ip != NULL; ip = ip->ifa_next) {
        if (ip->ifa_addr->sa_family == AF_INET && !strcmp(ip->ifa_name, "wlo1")) {
            return inet_ntoa(((struct sockaddr_in *)ip->ifa_addr)->sin_addr);
        }
    }
    return NULL;
}

int main()
{
    int socket = connect_to_server(get_ip_addr(), 8080);

    send_file(socket);
    close(socket);
}
