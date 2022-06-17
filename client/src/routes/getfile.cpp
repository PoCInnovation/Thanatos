#include "http_message.hpp"
#include <fstream>

static std::string get_file(const std::string file_name)
{
    std::ifstream stream(file_name);
    std::string file;

    while (stream.good()) {
        std::string line;
        std::getline(stream, line);
        file += line + "\n";
    }
    return file;
}

void get_file_route(int socket, HttpMessage &request)
{
    std::string file_path = request.get_body();
    std::string file_content = get_file(file_path);
    HttpMessage answer(HttpMessage::HttpMethod::POST, "0.0.0.0", "/get_file");

    answer.send_message(socket);
}
