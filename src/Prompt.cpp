/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Prompt
*/

#include "Prompt.hpp"
#include "Errors.hpp"
#include <iostream>

static const std::map<std::string, plazza::PizzaType> type_map = {
    {"regina", plazza::Regina}, {"margarita", plazza::Margarita},
    {"americana", plazza::Americana}, {"fantasia", plazza::Fantasia}};
static const std::map<std::string, plazza::PizzaSize> size_map = {
    {"S", plazza::S}, {"M", plazza::M}, {"L", plazza::L}, {"XL", plazza::XL},
    {"XXL", plazza::XXL}};

plazza::Order plazza::Prompt::readOrder()
{
    Order order;
    std::vector<plazza::Pizza> pizzas;
    std::vector<std::string> splitted_orders;
    std::vector<std::string> splitted_str;
    std::string line;
    int count = 0;

    std::getline(std::cin, line);
    if (line == "")
        return order;
    if (line == "status") {
        order.setStatus(true);
        return order;
    }
    splitted_orders = splitString(line, ';');
    for (auto &order : splitted_orders) {
        splitted_str = splitString(order, ' ');
        if (splitted_str.size() != 3)
            throw plazza::PromptErrors();
        splitted_str[2] = splitted_str[2].substr(1);
        count = std::stoi(splitted_str[2]);
        for (int i = 0; i < count; i++)
            pizzas.push_back(pizza_t{type_map.at(splitted_str[0]),
                size_map.at(splitted_str[1]), 0});
    }
    if (pizzas.size())
        order.open(pizzas);
    return order;
}

plazza::Order plazza::Prompt::getOrder() noexcept
{
    Order order;
    std::vector<Pizza> pizzas;
    fd_set set;
    struct timeval timeout;

    timeout.tv_sec = 0;
    timeout.tv_usec = 100;
    FD_ZERO(&set);
    FD_SET(0, &set);
    if (!select(1, &set, NULL, NULL, &timeout))
        return order;
    try {
        order = readOrder();
    } catch (const std::exception &e) {
        std::cerr << "Invalid command" << std::endl;
    }
    return order;
}

bool plazza::Prompt::sigStop() noexcept { return stop; }
