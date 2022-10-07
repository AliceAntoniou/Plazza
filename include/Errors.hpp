/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Errors
*/

#pragma once

#include <string>

namespace plazza
{
    class Error : public std::exception {
        public:
            Error(std::string const &message) noexcept;
            virtual char const *what() const noexcept;

        protected:
            std::string _message;
    };
    class parserErrors : public plazza::Error {
        public:
            parserErrors(std::string const &message) noexcept;
    };
    class PromptErrors : public plazza::Error {
        public:
            PromptErrors() noexcept;
    };
    class ProcessError : public plazza::Error {
        public:
            ProcessError() noexcept;
    };
}
