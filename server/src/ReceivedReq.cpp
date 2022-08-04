#include "ReceivedReq.hpp"

void ReceivedReq::add_header(const std::string &key, const std::string &value)
{
    this->parameters[key] = value;
}

static void get_headers(ReceivedReq &received_req, std::stringstream &raw_message)
{
    std::string parameter;
    std::string key;
    std::string value;

    while (std::getline(received, header, '\n')) {
        if (header == "\r")
            break;
        std::getline(received, key, '=');
        std::getline(received, value, '\n');
        received_req.set_header(key, value);
    }
}

ReceivedReq::ReceivedReq(std::stringstream &raw_message)
{
    std::string file_name_buffer;
    std::stringstream file_content_buffer;

    get_headers(this, raw_message);
    while (std::getline(raw_message, file_name_buffer, "\r\n")) {
        std::getline(raw_message, file_content_buffer, "\r\n");
        this->files.push_back(std::make_pair<std::string, std::string>(file_name_buffer, file_content_buffer));
    }
}
