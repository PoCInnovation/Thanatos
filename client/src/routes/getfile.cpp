#include "http_res.hpp"
#include "http_req.hpp"
#include <fstream>

static std::string get_file(const std::string file_name)
{
    std::ifstream stream(file_name);
    std::string file;

    while (stream.good()) {
        std::string line;
        std::getline(stream, line);
        file += line + "\n";
    }
    return file;
}

void get_file_route(HttpReq req, HttpRes res)
{
    std::string file_path = req.get_body();
    std::string file_content = get_file(file_path);

    if (file_content.empty()) {
        res.set_status("404");
        res << "File not found";
    } else {
        res.set_status("200");
        res << file_content;
    }
}
