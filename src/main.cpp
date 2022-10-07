/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** main
*/

#include "Errors.hpp"
#include "Reception.hpp"
#include <iostream>

int main(int argc, char const *argv[])
{
    plazza::args_t args;
    plazza::Reception reception;

    try {
        args = plazza::parse(argc, argv);
    } catch (const plazza::parserErrors &e) {
        std::cerr << e.what() << std::endl;
        return 84;
    }
    reception.start(args);
    return 0;
}
