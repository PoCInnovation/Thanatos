#include "manage_messages.hpp"
#include "http_res.hpp"
#include "http_req.hpp"
#include <string.h>

static HttpReq::HttpMethod destringify_method(std::string &string)
{
    if (string == "GET")
        return HttpReq::HttpMethod::GET;
    if (string == "POST")
        return HttpReq::HttpMethod::POST;
    else
        return HttpReq::HttpMethod::GET;
}

static std::string get_body(std::stringstream &received)
{
    std::string body;
    std::getline(received, body, '\0');
    return body;
}

static void get_headers_req(HttpReq &http_message, std::stringstream &received)
{
    std::string header;
    std::string key;
    std::string value;

    while (std::getline(received, header, '\n')) {
        if (header == "\r")
            break;
        std::getline(received, key, ':');
        std::getline(received, value, '\n');
        value.erase(0, 1);
        http_message.set_header(key, value);
    }
}

static void get_headers_res(HttpRes &http_message, std::stringstream &received)
{
    std::string header;
    std::string key;
    std::string value;

    while (std::getline(received, header, '\n')) {
        if (header == "\r")
            break;
        std::getline(received, key, ':');
        std::getline(received, value, '\n');
        value.erase(0, 1);
        http_message.set_header(key, value);
    }
}

HttpRes convert_res(int socket)
{
    std::stringstream string_received;
    char char_readed = 'a';

    while (recv(socket, &char_readed, 1, 0) && char_readed != '\0') {
        string_received << char_readed;
    }
    std::string version;
    std::getline(string_received, version, ' ');
    std::string status;
    std::getline(string_received, status, ' ');
    std::getline(string_received, status, ' ');
    HttpRes res = HttpRes("0.0.0.0", status, version);
    get_headers_res(res, string_received);
    res << get_body(string_received);
    return res;
}

HttpReq convert_req(int socket)
{
    std::stringstream string_received;
    char char_readed = 'a';
    HttpReq::HttpMethod method = HttpReq::HttpMethod::GET;

    while (recv(socket, &char_readed, 1, 0) && char_readed != '\0') {
        string_received << char_readed;
    }
    std::string request_info;
    std::getline(string_received, request_info, ' ');
    method = destringify_method(request_info);
    std::string route;
    std::getline(string_received, route, ' ');
    std::string version;
    std::getline(string_received, version, ' ');
    HttpReq req = HttpReq(method, "0.0.0.0", route, version);
    get_headers_req(req, string_received);
    req << get_body(string_received);
    return req;
}
