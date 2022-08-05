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

void getFiles(MessageReceiver &messageReceiver, std::stringstream &message)
{
    // pair of file names and file content
    std::pair<std::string, std::string> file;

    while (true) {
        std::getline(message, file.first, '\n');
        std::getline(message, file.second, static_cast<char>(0x03));
        if (message.eof())
            break;
        messageReceiver.files.push_back(file);
    }
}

MessageReceiver::MessageReceiver(std::stringstream &message)
{
    getHeader(*this, message);
    getFiles(*this, message);
}
