#ifndef __MANAGE_MESSAGES_HPP__
    #define __MANAGE_MESSAGES_HPP__
    #include "http_res.hpp"
    #include "http_req.hpp"

HttpReq convert_req(int socket);
HttpRes convert_res(int socket);
void get_file_route(HttpReq req, HttpRes res);
void redirect_route(HttpReq req, HttpRes res);
void connect(int socket);
void do_loop(int socket);
std::string get_file(const std::string file_name);
void send_file(int socket);
std::string get_files(const std::string file_name);

#endif
