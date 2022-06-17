#include "manage_messages.hpp"
#include "http_message.hpp"
#include <string>

static HttpMessage::HttpMethod destringify_method(std::string &string)
{
    if (string == "GET")
        return HttpMessage::HttpMethod::GET;
    if (string == "POST")
        return HttpMessage::HttpMethod::POST;
    else
        return HttpMessage::HttpMethod::GET;
}

static void get_headers(HttpMessage &http_message, std::stringstream &received)
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

static void get_body(HttpMessage &http_message, std::stringstream &received)
{
    std::string body;
    std::getline(received, body, '\0');
    http_message << body;
}

// https://stackoverflow.com/questions/20011851/does-stringstream-read-consume-the-stream
HttpMessage receive_message(int socket)
{
    std::stringstream string_received;
    char char_readed = 'a';
    HttpMessage::HttpMethod method = HttpMessage::HttpMethod::GET;

    while (recv(socket, &char_readed, 1, 0) && char_readed != '\0') {
        string_received << char_readed;
    }
    std::string request_info;
    std::getline(string_received, request_info, ' ');
    method = destringify_method(request_info);
    std::string route;
    std::getline(string_received, route, ' ');
    auto http_message = HttpMessage(method, "0.0.0.0", route);

    get_headers(http_message, string_received);
    get_body(http_message, string_received);
    return http_message;
}
