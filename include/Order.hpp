/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Order
*/

#pragma once

#include "Pizza.hpp"
#include <list>
#include <vector>

namespace plazza
{
    class Order {
        public:
            Order(void) noexcept = default;

            Order(const Order &) noexcept = default;
            Order(Order &&) noexcept = default;
            ~Order(void) noexcept = default;

            Order &operator=(const Order &) noexcept = default;
            Order &operator=(Order &&) noexcept = default;

            std::vector<Pizza> read() noexcept;
            bool isFinished() const noexcept;
            bool isEmpty() const noexcept;
            bool isStatus() const noexcept;
            void setStatus(bool) noexcept;
            void open(std::vector<Pizza> &) noexcept;
            bool isOpen() const noexcept;
            void close() noexcept;
            void operator<<(std::list<Pizza> &) noexcept;

        private:
            std::vector<Pizza> pizzas;
            bool is_open = false;
            size_t size = 0;
            size_t id;
            bool is_status = false;
    };
}
