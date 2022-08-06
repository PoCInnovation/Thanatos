#ifndef __MANAGE_MESSAGES_HPP__
    #define __MANAGE_MESSAGES_HPP__
    #include "req.hpp"

void get_files_contents(Req &request);
std::string get_file(const std::string file_name);

#endif
