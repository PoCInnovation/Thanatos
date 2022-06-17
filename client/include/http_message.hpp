#ifndef __HTTP_MESSAGE_HPP__
    #define __HTTP_MESSAGE_HPP__
    #include <iostream>
    #include <sstream>
    #include <map>
    #include <sys/socket.h>
    #include <unistd.h>

class HttpMessage
{
public:
    enum class HttpMethod {
        GET,
        POST,
    };
private:
    HttpMethod method;
    std::string body_content;
    std::string request_string;
    std::string route;
    std::map<std::string, std::string> headers;

    std::string stringify_method() {
        switch (this->method) {
            case HttpMethod::GET:
                return "GET";
                break;
            case HttpMethod::POST:
                return "POST";
        }
        return "";
    }
public:
    HttpMessage(HttpMethod method, const std::string &url,
        const std::string &route)
    {
        this->method = method;
        this->route = route;
        set_header("Host", url);
    }

    HttpMessage &operator <<(const std::string &body_message)
    {
        this->body_content.append(body_message);
        return *this;
    }

    void print_message()
    {
        std::cout << stringify_method();
        std::cout << " " << this->route << " " << "HTTP/1.1" << std::endl;
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

        http_message_encoded << stringify_method();
        http_message_encoded << " " << this->route << " " << "HTTP/1.1\r\n";
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
