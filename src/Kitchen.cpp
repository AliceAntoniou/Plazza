/*
** EPITECH PROJECT, 2022
** Kitchen
** File description:
** Kitchen
*/

#include "Kitchen.hpp"
#include "Errors.hpp"
#include <fstream>
#include <iostream>
#include <signal.h>
#include <sstream>

static size_t getId()
{
    static size_t id;

    return id++;
}

plazza::Kitchen::Kitchen(args_t param)
    : cooks_nbr(param.cooks_nbr), restock_time(param.restock_time),
      multiplier(param.multiplier), id(getId())
{
}

plazza::Kitchen::Kitchen(float multiplier_, int cooks_nbr_, int restock_time_)
    : cooks_nbr(cooks_nbr_), restock_time(restock_time_),
      multiplier(multiplier_), id(getId())
{
}

void plazza::Kitchen::start() noexcept
{
    if (process.pFork()) {
        return;
    }
    for (int i = 0; i < cooks_nbr; i++) {
        cooks.push_back(Cook(multiplier));
    }
    try {
        launch();
    } catch (const ProcessError &) {
    }
    exit(0);
}

void plazza::Kitchen::operator<<(std::vector<Pizza> &pizzas) noexcept
{
    int count = 0;
    pizza_t tmp;

    if (process.isDead())
        return;
    try {
        count = process.pRead<int>();
        if (count > (int) pizzas.size())
            count = pizzas.size();
        process.pWrite(count);
        while (count > 0) {
            tmp = pizzas.back().pack();
            process.pWrite(tmp);
            pizzas.pop_back();
            count--;
        };
    } catch (const ProcessError &) {
    }
}

bool plazza::Kitchen::isDead() const noexcept { return process.isDead(); }

std::vector<plazza::Pizza> plazza::Kitchen::getFinishedPizza() noexcept
{
    std::vector<Pizza> pizzas(0);

    if (process.isDead())
        return pizzas;
    try {
        for (int i = process.pRead<int>(); i > 0; i--) {
            pizzas.push_back(process.pRead<pizza_t>());
        }
    } catch (const ProcessError &) {
    }
    return pizzas;
}

void plazza::Kitchen::checkStatus()
{
    if (process.pRead<int>() == 1) {
        std::cout << "\twaitlist " << waiting.size() << ":\n";
        for (auto &&i : waiting) {
            std::cout << "\t\t" << i.dump() << '\n';
        }
        printStatus(true);
    }
}

bool plazza::Kitchen::getPizza()
{
    bool check = false;

    process.pWrite(cooks_nbr - waiting.size());
    for (int i = process.pRead<int>(); i > 0; i--) {
        waiting.push_back(process.pRead<pizza_t>());
        check = true;
    }
    return check;
}

void plazza::Kitchen::sendFinished()
{
    process.pWrite(finished.size());
    for (int i = finished.size(); i > 0; i--) {
        process.pWrite(finished.back().pack());
        finished.pop_back();
    }
}

bool plazza::Kitchen::manageCooks() noexcept
{
    bool check;

    for (auto &cook : cooks) {
        if (cook.ended()) {
            finished.push_back(cook.getFinished());
            check = true;
        }
        for (std::list<Pizza>::iterator i = waiting.begin();
             waiting.size() && i != waiting.end(); i++) {
            if (!i->takeIngredients(ingredients))
                continue;
            if (cook.prepare(waiting.front())) {
                check = true;
                i = waiting.erase(waiting.begin());
                break;
            }
        }
    }
    return check;
}

void plazza::Kitchen::launch()
{
    auto refill = std::chrono::system_clock::now();
    auto life = std::chrono::system_clock::now();

    while (5000000000 > (std::chrono::system_clock::now() - life).count()) {
        for (int64_t i = (std::chrono::system_clock::now() - refill).count();
             i > restock_time * 1000000; i -= restock_time * 1000000) {
            refill = std::chrono::system_clock::now();
            ingredients++;
        }
        checkStatus();
        if (getPizza())
            life = std::chrono::system_clock::now();
        if (manageCooks())
            life = std::chrono::system_clock::now();
        sendFinished();
        if (waiting.size())
            life = std::chrono::system_clock::now();
    }
}

void plazza::Kitchen::printStatus(bool print) const noexcept
{
    std::stringstream s;

    try {
        if (!print) {
            process.pWrite(0);
            return;
        }
        if (process.isChild()) {
            process.pWrite(1);
            return;
        }
    } catch (const ProcessError &) {
        return;
    }
    s << "Kitchen #" << id + 1 << ":" << '\n';
    s << "\tIngredients:" << '\n';
    s << "\t\tDoe: " << ingredients.doe << '\n';
    s << "\t\tTomato: " << ingredients.tomato << '\n';
    s << "\t\tGruyere: " << ingredients.gruyere << '\n';
    s << "\t\tHam: " << ingredients.ham << '\n';
    s << "\t\tMushrooms: " << ingredients.mushrooms << '\n';
    s << "\t\tSteak: " << ingredients.steak << '\n';
    s << "\t\tEegplant: " << ingredients.eggplant << '\n';
    s << "\t\tGoat cheese: " << ingredients.goat_cheese << '\n';
    for (size_t i = 0; i < cooks.size(); i++) {
        s << "\tCook #" << i + 1 << " is " << cooks[i].getStatus() << '\n';
    }
    std::cout << s.str() << std::endl;
}
