/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Order
*/

#include "Order.hpp"
#include <fstream>
#include <iostream>

std::vector<plazza::Pizza> plazza::Order::read() noexcept
{
    std::vector<plazza::Pizza> tmp = pizzas;

    pizzas.clear();
    return tmp;
}

void plazza::Order::operator<<(std::list<Pizza> &pizzas_) noexcept
{
    for (std::list<Pizza>::iterator i = pizzas_.begin();
         pizzas_.size() && i != pizzas_.end(); i++) {
        if (i->getId() == id) {
            pizzas.push_back(*i);
        }
    }
    pizzas_.clear();
}

void plazza::Order::open(std::vector<plazza::Pizza> &pizzas_) noexcept
{
    static size_t ref_id;

    id = ref_id++;
    is_open = true;
    pizzas = pizzas_;
    pizzas_.clear();
    for (auto &&pizza : pizzas) {
        pizza.setId(id);
    }
    size = pizzas.size();
    log("Order #" + std::to_string(id) + " create.\n");
}

void plazza::Order::close() noexcept
{
    log("Order #" + std::to_string(id) + " done.\n");
}

bool plazza::Order::isFinished() const noexcept
{
    return size == pizzas.size();
}

bool plazza::Order::isEmpty() const noexcept { return size == 0; }

bool plazza::Order::isOpen() const noexcept { return is_open; }

bool plazza::Order::isStatus() const noexcept { return is_status; }

void plazza::Order::setStatus(bool status) noexcept { is_status = status; }
