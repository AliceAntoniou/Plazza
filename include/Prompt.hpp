/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Prompt
*/

#pragma once

#include "Order.hpp"
#include "Process.hpp"
#include <vector>

namespace plazza
{
    class Prompt {
        public:
            Prompt(void) noexcept = default;

            Prompt(const Prompt &) noexcept = delete;
            Prompt(Prompt &&) noexcept = delete;
            ~Prompt(void) noexcept = default;

            Prompt &operator=(const Prompt &rhs) noexcept = delete;
            Prompt &operator=(Prompt &&rhs) noexcept = delete;

            Order getOrder() noexcept;
            bool sigStop() noexcept;

        private:
            bool stop = false;
            static Order readOrder();
    };
}
