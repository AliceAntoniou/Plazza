/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Pizza
*/

#include "Pizza.hpp"

plazza::Pizza::Pizza(PizzaSize size_, PizzaType type_, int id_)
    : size(size_), type(type_), id(id_)
{
}

plazza::Pizza::Pizza(const pizza_t &pizza)
    : size(pizza.size), type(pizza.type), id(pizza.id)
{
}

plazza::pizza_t plazza::Pizza::pack() const noexcept
{
    return pizza_t{type, size, id};
}

int plazza::Pizza::getCookTime() const noexcept
{
    static const std::map<plazza::PizzaType, int> time_map{
        {plazza::Regina, 1000}, {plazza::Margarita, 2000},
        {plazza::Americana, 2000}, {plazza::Fantasia, 4000}};

    return time_map.at(type);
}

void plazza::Pizza::setId(size_t id_) noexcept { id = id_; }

size_t plazza::Pizza::getId() const noexcept { return id; }

std::string plazza::Pizza::dump() const noexcept
{
    static const std::map<plazza::PizzaType, std::string> type_str = {
        {plazza::Regina, "Regina"}, {plazza::Margarita, "Margarita"},
        {plazza::Americana, "Americana"}, {plazza::Fantasia, "Fantasia"}};
    static const std::map<plazza::PizzaSize, std::string> size_str = {
        {plazza::S, "S"}, {plazza::M, "M"}, {plazza::L, "L"},
        {plazza::XL, "XL"}, {plazza::XXL, "XXL"}};

    try {
        return type_str.at(type) + " " + size_str.at(size);
    } catch (const std::exception &e) {
        return "Unknow Pizza";
    }
}

bool plazza::Pizza::takeIngredients(ingredients_t &ing) noexcept
{
    static const std::map<plazza::PizzaType, plazza::ingredients_t> recipe = {
        {plazza::Margarita, plazza::ingredients_t{1, 1, 1, 0, 0, 0, 0, 0}},
        {plazza::Regina, plazza::ingredients_t{1, 1, 1, 1, 1, 0, 0, 0}},
        {plazza::Americana, plazza::ingredients_t{1, 1, 1, 0, 0, 1, 0, 0}},
        {plazza::Fantasia, plazza::ingredients_t{1, 1, 0, 0, 0, 0, 1, 1}}};

    try {
        recipe.at(type);
    } catch (const std::exception &e) {
        return false;
    }
    if (recipe.at(type) <= ing) {
        ing -= recipe.at(type);
        return true;
    }
    return false;
}

bool plazza::operator<=(
    const ingredients_t &ing_1, const ingredients_t &ing2) noexcept
{
    return (ing_1.doe <= ing2.doe && ing_1.tomato <= ing2.tomato &&
        ing_1.gruyere <= ing2.gruyere && ing_1.ham <= ing2.ham &&
        ing_1.mushrooms <= ing2.mushrooms && ing_1.steak <= ing2.steak &&
        ing_1.eggplant <= ing2.eggplant &&
        ing_1.goat_cheese <= ing2.goat_cheese);
}

void plazza::operator-=(
    ingredients_t &ing_1, const ingredients_t &ing2) noexcept
{
    ing_1.doe -= ing2.doe;
    ing_1.tomato -= ing2.tomato;
    ing_1.gruyere -= ing2.gruyere;
    ing_1.ham -= ing2.ham;
    ing_1.mushrooms -= ing2.mushrooms;
    ing_1.steak -= ing2.steak;
    ing_1.eggplant -= ing2.eggplant;
    ing_1.goat_cheese -= ing2.goat_cheese;
}

void plazza::operator++(ingredients_t &ing, int n) noexcept
{
    n++;
    if (ing.doe < 5)
        ing.doe += n;
    if (ing.tomato < 5)
        ing.tomato += n;
    if (ing.gruyere < 5)
        ing.gruyere += n;
    if (ing.ham < 5)
        ing.ham += n;
    if (ing.mushrooms < 5)
        ing.mushrooms += n;
    if (ing.steak < 5)
        ing.steak += n;
    if (ing.eggplant < 5)
        ing.eggplant += n;
    if (ing.goat_cheese < 5)
        ing.goat_cheese += n;
}
