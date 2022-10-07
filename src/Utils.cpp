/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Utils
*/

#include "Utils.hpp"
#include "Errors.hpp"
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/select.h>
#include <unistd.h>

plazza::args_t plazza::parse(int argc, char const *argv[])
{
    args_t args;

    if (argc != 4)
        throw plazza::parserErrors(
            "Wrong args nbr (<multiplier> <cooks nbr> <restock time>)");
    try {
        args.multiplier = std::stof(argv[1]);
    } catch (const std::exception &e) {
        throw plazza::parserErrors(
            "Invalid first arg (must be a positive float)");
    }
    if (args.multiplier <= 0)
        throw plazza::parserErrors("Invalid first arg (must be >0)");
    try {
        args.cooks_nbr = std::stoi(argv[2]);
    } catch (const std::exception &e) {
        throw plazza::parserErrors(
            "Invalid second arg (must be a positive int)");
    }
    if (args.cooks_nbr <= 0)
        throw plazza::parserErrors("Invalid second arg (must be >0)");
    try {
        args.restock_time = std::stoi(argv[3]);
    } catch (const std::exception &e) {
        throw plazza::parserErrors("Invalid third arg (must be an int)");
    }
    if (args.restock_time < 0)
        throw plazza::parserErrors("Invalid third arg (must be >=0");
    return args;
}

std::vector<std::string> plazza::splitString(
    std::string str, char delim) noexcept
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (std::getline(tokenStream, token, delim)) {
        if (token.length() > 0)
            tokens.push_back(token);
    }
    return (tokens);
}

void plazza::log(std::string str) noexcept
{
    static int fd;
    fd_set set;

    if (!fd) {
        fclose(fopen("order.log", "w"));
        fd = open("order.log", O_APPEND | O_WRONLY);
    }
    FD_ZERO(&set);
    FD_SET(fd, &set);
    select(fd + 1, NULL, &set, NULL, NULL);
    write(fd, str.c_str(), str.length());
}