#include "http_message.hpp"

void connect(int socket)
{
    HttpMessage connect_message(HttpMessage::HttpMethod::POST, "/connect",
        "0.0.0.0");

    connect_message.send_message(socket);
}
