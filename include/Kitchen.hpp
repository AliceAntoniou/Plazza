/*
** EPITECH PROJECT, 2022
** Kitchen
** File description:
** Kitchen
*/

#pragma once

#include "Cook.hpp"
#include "Process.hpp"
#include <Utils.hpp>
#include <list>
#include <unistd.h>
#include <vector>

namespace plazza
{
    class Kitchen {
        public:
            Kitchen(void) noexcept = delete;
            Kitchen(args_t param);
            Kitchen(float multiplier, int cook_nbr, int restock_time);

            Kitchen(const Kitchen &) noexcept = delete;
            Kitchen(Kitchen &&) noexcept = default;
            ~Kitchen(void) noexcept = default;

            Kitchen &operator=(const Kitchen &rhs) noexcept = delete;
            Kitchen &operator=(Kitchen &&rhs) noexcept = default;

            bool isDead() const noexcept;
            void start() noexcept;
            void operator<<(std::vector<Pizza> &) noexcept;
            std::vector<Pizza> getFinishedPizza() noexcept;
            void printStatus(bool) const noexcept;

        private:
            void launch();
            void checkStatus();
            bool getPizza();
            void sendFinished();
            bool manageCooks() noexcept;
            int cooks_nbr;
            int restock_time;
            float multiplier;
            ingredients_t ingredients;
            size_t id;
            std::vector<Cook> cooks;
            std::list<Pizza> waiting;
            std::vector<Pizza> finished;
            Process process;
    };
}
