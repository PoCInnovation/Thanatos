#ifndef __HTTP_REQ_HPP__
    #define __HTTP_REQ_HPP__
    #include <iostream>
    #include <sstream>
    #include <map>
    #include <sys/socket.h>
    #include <unistd.h>

class Req
{
private:
    std::string hwid;
    std::string body_content;
    std::string request_string;
    std::map<std::string, std::string> headers;

public:
    Req(std::string hwid)
    {
        this->hwid = hwid;
    }

    Req &operator <<(const std::string &body_message)
    {
        this->body_content.append(body_message);
        return *this;
    }

    void print_message()
    {
        for (const auto& [key, val] : headers) {
            std::cout << key << ": " << val << std::endl;
        }
        std::cout << "\n";
        std::cout << body_content << std::endl;
    }

    void set_header(const std::string &key, const std::string &content)
    {
        headers[key] = content;
    }

    std::string get_header(const std::string &key)
    {
        return headers.at(key);
    }

    void send_message(int socket)
    {
        std::stringstream http_message_encoded;
        std::string http_message;

        for (const auto& [key, val] : headers) {
            http_message_encoded << key << "=" << val << "\n";
        }
        http_message_encoded << "\r\n";
        http_message_encoded << body_content << "\r\n";
        http_message = http_message_encoded.str();
        write(socket, http_message.c_str(), http_message.length());
    }

    void push_file_to_req(std::string &file_name, std::string &file_content)
    {
        body_content.append(file_name);
        body_content.append("\r\n");
        body_content.append(file_content);
        body_content.append("\r\n");
    }

    std::string &get_body() {
        return this->body_content;
    }
};

#endif
