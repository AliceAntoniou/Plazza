/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#include "Reception.hpp"
#include <iostream>
#include <sys/stat.h>

void plazza::Reception::sendToKitchens()
{
    std::list<Kitchen> new_kitchens;

    for (auto &kitchen : kitchens) {
        for (auto &&pizza : kitchen.getFinishedPizza())
            finished.push_back(pizza);
        if (!kitchen.isDead())
            new_kitchens.push_back(std::move(kitchen));
    }
    kitchens = std::move(new_kitchens);
}

void plazza::Reception::getOrder(Order &order)
{
    if (order.isStatus() && kitchens.size() == 0)
        std::cout << "No open kitchen" << std::endl;
    for (auto &kitchen : kitchens) {
        kitchen.printStatus(order.isStatus());
        usleep(10);
    }
    if (order.isOpen()) {
        for (auto &pizza : order.read()) {
            pizzas.push_back(pizza);
        }
        orders.push_back(order);
    }
}

void plazza::Reception::checkOrders()
{
    std::list<Order> new_orders;

    for (auto &order : orders) {
        order << finished;
        if (order.isFinished()) {
            order.close();
        } else
            new_orders.push_back(std::move(order));
    }
    orders = new_orders;
}

void plazza::Reception::order(Order order) noexcept
{
    getOrder(order);
    for (auto &kitchen : kitchens) {
        kitchen << pizzas;
    }
    sendToKitchens();
    while (pizzas.size() > kitchens.size() * param.cooks_nbr * 2) {
        kitchens.push_back(Kitchen(param));
        kitchens.back().start();
    }
    checkOrders();
    finished.clear();
}

void plazza::Reception::start(plazza::args_t args) noexcept
{
    Prompt prompt;

    system("rm -rf tmp");
    mkdir("tmp/", 0777);
    param = args;
    while (!prompt.sigStop()) {
        order(prompt.getOrder());
    }
}