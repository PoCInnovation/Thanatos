#ifndef __HTTP_MESSAGE_HPP__
    #define __HTTP_MESSAGE_HPP__
    #include <iostream>
    #include <sstream>
    #include <map>
#include <utility>

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
    std::string path;
    std::map<std::string, std::string> headers;
    void print_method() {
        switch (this->method) {
            case HttpMethod::GET:
                std::cout << "GET";
                break;
            case HttpMethod::POST:
                std::cout << "POST";
        }
    }
public:
    HttpMessage(HttpMethod method, const std::string &url,
        const std::string &path)
    {
        this->method = method;
        this->path = path;
        set_header("Host", url);
    }

    HttpMessage &operator <<(const std::string &body_message)
    {
        this->body_content.append(body_message);
        return *this;
    }

    void print_message()
    {
        print_method();
        std::cout << " " << this->path << " " << "HTTP/1.1" << std::endl;
        for (const auto& [key, val] : headers) {
            std::cout << key << ": " << val << std::endl;
        }
        std::cout << body_content << std::endl;
    }

    void set_header(const std::string &key, const std::string &content)
    {
        headers[key] = content;
    }
};

#endif
