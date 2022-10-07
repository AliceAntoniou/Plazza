/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Process
*/

#pragma once

#include "Errors.hpp"
#include "Utils.hpp"
#include <signal.h>
#include <string>
#include <unistd.h>
#include <wait.h>

class Process {
    public:
        Process(void) noexcept = default;

        Process(const Process &) noexcept = delete;
        Process(Process &&) noexcept = default;
        ~Process(void) noexcept = default;

        Process &operator=(const Process &) noexcept = delete;
        Process &operator=(Process &&) noexcept = default;

        bool isChild() const noexcept;
        bool pFork() noexcept;
        int pKill(int sig) const noexcept;
        bool isDead() const noexcept;
        void pWait() const noexcept;
        bool canRead() const noexcept;
        void pWrite(int) const;
        void pWrite(const plazza::pizza_t &) const;

        template <class T> T pRead() const
        {
            T buf;
            fd_set set;
            struct timeval timeout;

            timeout.tv_sec = pid ? 1 : 10;
            timeout.tv_usec = 0;
            FD_ZERO(&set);
            FD_SET(readfd, &set);
            if (!select(readfd + 1, &set, NULL, NULL, &timeout))
                throw plazza::ProcessError();
            read(readfd, &buf, sizeof(T));
            return buf;
        };

    private:
        pid_t pid = -1;
        int readfd = -1;
        int writefd = -1;
};