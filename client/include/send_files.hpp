#ifndef __MANAGE_MESSAGES_HPP__
#define __MANAGE_MESSAGES_HPP__
#include "req.hpp"
#include <optional>

void get_files_contents(Req &request, std::string username);
std::optional<std::string> get_file(const std::string file_name);

#endif
