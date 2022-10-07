/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Reception
*/

#pragma once

#include "Kitchen.hpp"
#include "Order.hpp"
#include "Prompt.hpp"
#include <list>
#include <vector>

namespace plazza
{
    class Reception {
        public:
            Reception(void) noexcept = default;

            Reception(const Reception &) noexcept = delete;
            Reception(Reception &&) noexcept = delete;
            ~Reception(void) noexcept = default;

            Reception &operator=(const Reception &) noexcept = delete;
            Reception &operator=(Reception &&) noexcept = delete;

            void start(plazza::args) noexcept;

        private:
            void sendToKitchens();
            void getOrder(Order &);
            void checkOrders();
            void order(Order) noexcept;
            args_t param;
            std::vector<Pizza> pizzas;
            std::list<Order> orders;
            std::list<Kitchen> kitchens;
            std::list<Pizza> finished;
    };
}
