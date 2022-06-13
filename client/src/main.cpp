#include "http_message.hpp"
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
    auto message = HttpMessage(HttpMessage::HttpMethod::GET, "0.0.0.0",
        "/hello.html");

    message << "Salut je suis le body";
    message << "\nhaha salut";
    message.set_header("cle", "haha pas clé haha");
    message.print_message();
}
