/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Cook
*/

#include "Cook.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <unistd.h>

plazza::Cook::Cook(float multiplier_) : multiplier(multiplier_) {}

plazza::Cook::Cook(Cook &&cook) noexcept
{
    begin = cook.begin;
    multiplier = cook.multiplier;
}

void cookf(plazza::Pizza pizza, float multiplier, std::mutex *working)
{
    int cook_time = pizza.getCookTime() * multiplier;

    working->lock();
    plazza::log("Prepare " + pizza.dump() + ".\n");
    // std::this_thread::sleep_for(std::chrono::milliseconds(cook_time));
    usleep(cook_time * 1000);
    plazza::log(pizza.dump() + " done.\n");
    working->unlock();
}

bool plazza::Cook::prepare(const Pizza &pizza_) noexcept
{
    if (begin || ended()) {
        pizza = pizza_;
        begin = false;
        thread = std::thread(cookf, pizza, multiplier, &working);
        return true;
    }
    return false;
}

bool plazza::Cook::ended() noexcept
{
    bool tmp;

    if (begin)
        return false;
    if ((tmp = working.try_lock()) == true) {
        working.unlock();
        begin = true;
    }
    return tmp;
}

plazza::Pizza plazza::Cook::getFinished() noexcept
{
    if (thread.joinable())
        thread.join();
    return pizza;
}

std::string plazza::Cook::getStatus() const noexcept
{
    if (!thread.joinable())
        return "idle";
    return "preparing " + pizza.dump();
}
