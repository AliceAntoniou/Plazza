/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Error
*/

#include "Errors.hpp"
#include <dlfcn.h>

plazza::Error::Error(std::string const &message) noexcept
    : _message("Plazza: " + message)
{
}

char const *plazza::Error::what() const noexcept { return _message.data(); }

plazza::parserErrors::parserErrors(std::string const &message) noexcept
    : plazza::Error("Parser: " + message)
{
}

plazza::PromptErrors::PromptErrors() noexcept
    : plazza::Error("Invalid command.")
{
}

plazza::ProcessError::ProcessError() noexcept : plazza::Error("No child") {}
