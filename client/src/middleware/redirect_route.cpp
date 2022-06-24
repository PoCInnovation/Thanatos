/*
** POC PROJECT, 2022
** redirect_route
** File description:
** redirect http message in route
*/

#include "http_res.hpp"
#include "http_req.hpp"
#include "manage_messages.hpp"
#include <string.h>

void redirect_route(HttpReq req, HttpRes res)
{
    std::string route(req.get_route());

    if (!strcmp(route.c_str(), "getfile")) {
        get_file_route(req, res);
    }
}
