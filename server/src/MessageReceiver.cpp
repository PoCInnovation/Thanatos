#include "MessageReceiver.hpp"
#include <iostream>
#include <string>

void getHeader(MessageReceiver &messageReceiver, std::stringstream &message)
{
    std::string parameter;
    std::string key;
    std::string value;

    while (std::getline(message, parameter, '\n')) {
        if (parameter == "\r")
            break;
        key = parameter.substr(0, parameter.find("="));
        value = parameter.substr(parameter.find("="));
        value.erase(0, 1);
        messageReceiver.setParameter(key, value);
    }
}

void getFiles(MessageReceiver &messageReceiver, std::stringstream &message,
    unsigned file_count)
{
    // pair of file names and file content
    std::pair<std::string, std::string> file;
    std::string file_content_len_str;
    unsigned file_content_len = 0;

    for (auto i = 0; i != file_count; ++i) {
        std::getline(message, file.first, '\n');
        std::getline(message, file_content_len_str, '\n');
        file_content_len = std::stoi(file_content_len_str);
        if (!file_content_len) {
            std::cout << "Invalid file length" << std::endl;
        }
        file.second.resize(file_content_len);
        message.read(&file.second[0], file_content_len);
        if (message.eof())
            break;
        messageReceiver.files.push_back(file);
    }
}

MessageReceiver::MessageReceiver(std::stringstream &message)
{
    unsigned file_count = 0;
    std::string file_count_str;

    std::getline(message, file_count_str, '\n');
    std::cout << "count " << file_count_str << std::endl;
    file_count = std::stoi(file_count_str);
    getHeader(*this, message);
    getFiles(*this, message, file_count);
}
