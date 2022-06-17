#include "http_message.hpp"

void connect(int socket)
{
    HttpMessage connect_message(HttpMessage::HttpMethod::POST, "0.0.0.0",
        "/connect");

    connect_message.send_message(socket);
}
