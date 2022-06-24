#include "http_req.hpp"

void connect(int socket)
{
    HttpReq connect_message(HttpReq::HttpMethod::POST, "0.0.0.0",
        "/connect", "HTTP/1.1");

    connect_message.send_message(socket);
}
