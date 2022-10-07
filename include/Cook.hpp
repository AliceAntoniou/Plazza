/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Cook
*/

#pragma once

#include "Pizza.hpp"
#include <mutex>
#include <thread>

namespace plazza
{
    class Cook {
        public:
            Cook(float multiplier);

            Cook(const Cook &) noexcept = delete;
            Cook(Cook &&) noexcept;
            ~Cook(void) noexcept = default;

            Cook &operator=(const Cook &) noexcept = delete;
            Cook &operator=(Cook &&) noexcept = delete;

            bool prepare(const Pizza &) noexcept;
            Pizza getFinished() noexcept;
            std::string getStatus() const noexcept;
            bool ended() noexcept;

        private:
            bool begin = true;
            float multiplier;
            std::mutex working;
            std::thread thread;
            Pizza pizza;
    };
}
