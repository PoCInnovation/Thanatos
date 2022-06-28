/*
** POC PROJECT, 2022
** loop
** File description:
** loop between server and client
*/

#include "http_res.hpp"
#include "http_req.hpp"
#include "manage_messages.hpp"

void do_loop(int socket)
{
    HttpReq req = HttpReq(HttpReq::HttpMethod::GET, "0.0.0.0", "/connect", "HTTP/1.1");
    req.send_message(socket);
    HttpRes res = convert_res(socket);

    if (res.get_status_code() != 200) {
        std::cerr << "Error: " << res.get_status_code() << std::endl;
        exit(84);
    }
    while (true) {
        convert_req(socket);
        redirect_route(req, res);
        res.send_message(socket);
    }
}
