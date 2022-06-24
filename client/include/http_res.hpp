#ifndef __HTTP_RES_HPP__
    #define __HTTP_RES_HPP__
    #include <iostream>
    #include <sstream>
    #include <map>
    #include <sys/socket.h>
    #include <unistd.h>

class HttpRes
{
public:
    enum class HttpMethod {
        GET,
        POST,
    };
private:
    std::string status;
    std::string version;
    std::string body_content;
    std::string request_string;
    std::map<std::string, std::string> headers;
public:

    HttpRes(const std::string &url, const std::string &status
        , const std::string &version)
    {
        this->status = status;
        this->version = version;
        set_header("Host", url);
    }

    HttpRes &operator <<(const std::string &body_message)
    {
        this->body_content.append(body_message);
        return *this;
    }

    void print_message()
    {
        std::cout << this->version << " " << this->status << std::endl;
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

    void set_status(const std::string &status)
    {
        this->status = status;
    }

    std::string get_header(const std::string &key)
    {
        return headers.at(key);
    }

    std::string get_status(void)
    {
        return this->status;
    }

    void send_message(int socket)
    {
        std::stringstream http_message_encoded;
        std::string http_message;

        http_message_encoded << this->version << " " << this->status << "\r\n";
        for (const auto& [key, val] : headers) {
            http_message_encoded << key << ": " << val << "\r\n";
        }
        http_message_encoded << "\r\n";
        http_message_encoded << body_content << "\r\n";
        http_message = http_message_encoded.str();
        write(socket, http_message.c_str(), http_message.length());
    }

    std::string &get_body() {
        return this->body_content;
    }
};

#endif
