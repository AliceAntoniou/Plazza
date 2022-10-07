/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Utils
*/

#pragma once

#include <string>
#include <vector>

namespace plazza
{
    void log(std::string str) noexcept;
    enum PizzaType { Regina = 1, Margarita = 2, Americana = 4, Fantasia = 8 };
    enum PizzaSize { S = 1, M = 2, L = 4, XL = 8, XXL = 16 };
    typedef struct packedPizza {
            PizzaType type;
            PizzaSize size;
            size_t id;
    } pizza_t;
    typedef struct args {
            float multiplier;
            int cooks_nbr;
            int restock_time;
    } args_t;
    args_t parse(int argc, char const *argv[]);
    std::vector<std::string> splitString(std::string str, char delim) noexcept;
}
