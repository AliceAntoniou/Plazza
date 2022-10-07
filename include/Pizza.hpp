/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#pragma once

#include <Utils.hpp>
#include <map>
#include <time.h>

namespace plazza
{
    typedef struct {
            int doe = 5;
            int tomato = 5;
            int gruyere = 5;
            int ham = 5;
            int mushrooms = 5;
            int steak = 5;
            int eggplant = 5;
            int goat_cheese = 5;
    } ingredients_t;
    bool operator<=(const ingredients_t &, const ingredients_t &) noexcept;
    void operator-=(ingredients_t &, const ingredients_t &) noexcept;
    void operator++(ingredients_t &, int) noexcept;
    class Pizza {
        public:
            Pizza(void) noexcept = default;
            Pizza(PizzaSize size, PizzaType type, int id = 0);
            Pizza(const pizza_t &);

            Pizza(const Pizza &) noexcept = default;
            Pizza(Pizza &&) noexcept = default;
            ~Pizza(void) noexcept = default;

            Pizza &operator=(const Pizza &) noexcept = default;
            Pizza &operator=(Pizza &&) noexcept = default;

            pizza_t pack() const noexcept;
            int getCookTime() const noexcept;
            void setId(size_t) noexcept;
            size_t getId() const noexcept;
            std::string dump() const noexcept;
            bool takeIngredients(ingredients_t &) noexcept;

        private:
            PizzaSize size;
            PizzaType type;
            size_t id;
    };
}
