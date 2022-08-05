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
        std::getline(message, key, '=');
        std::getline(message, value, '\n');
        std::cout << "key: " << key << std::endl;
        std::cout << "value: " << value << std::endl;
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
        messageReceiver.files.push_back(file);
        if (message.eof())
            break;
    }
}

MessageReceiver::MessageReceiver(std::stringstream &message)
{
    getHeader(*this, message);
    getFiles(*this, message);
}
