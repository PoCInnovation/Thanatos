#include <iostream>
#include <unistd.h>
#include <cstring>

int read_message(int socket_client)
{
    char buffer[4096];
    char *split;
    int status = 0;

    if (read(socket_client, buffer, 4096) == -1) {
        std::cout << "Error" << std::endl;
        return -1;
    }
    split = strtok(buffer, "\r\n");
    while (split != NULL) {
        split = strtok(NULL, "\r\n");
        if (!strcmp(split, "Connection: keep-alive")) {
            status = 1;
            break;
        }
    }
    return status;
}

std::string generate_response(int status)
{
    std::string version("HTTP/1.1 200 OK\r\nContent-Length: 6\r\n");
    std::string parameter_status("");
    std::string message("SUCESS");
    std::string result("");

    if (status)
        parameter_status = "Connection: keep-alive\r\n\r\n";
    else
        parameter_status = "Connection: close\r\n\r\n";
    result = version + parameter_status + message;
    return result;
}

void send_message(int socket_client, int status)
{
    std::string tmp = generate_response(status);
    const char *message = tmp.c_str();

    write(socket_client, message, strlen(message));
    std::cout << "Send Sucess !" << std::endl;
}

void relation_client(int socket_client)
{
    int status = 1;

    while (status) {
        status = read_message(socket_client);
        send_message(socket_client, status);
    }
}
