/*
** EPITECH PROJECT, 2022
** plazza
** File description:
** Process
*/

#include "Process.hpp"
#include <fcntl.h>
#include <iostream>
#include <istream>
#include <sys/mman.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>

void my_pipe(int fd[2])
{
    static int id;
    std::string path("tmp/");

    path += std::to_string(id++);
    mkfifo(path.c_str(), 0666);
    fd[0] = open(path.c_str(), O_NONBLOCK | O_RDONLY);
    fd[1] = open(path.c_str(), O_NONBLOCK | O_WRONLY);
}

bool Process::pFork() noexcept
{
    int parent_fd[2];
    int child_fd[2];

    my_pipe(parent_fd);
    my_pipe(child_fd);
    pid = fork();
    if (!pid) {
        readfd = parent_fd[0];
        writefd = child_fd[1];
        return false;
    }
    readfd = child_fd[0];
    writefd = parent_fd[1];
    return true;
}

bool Process::isChild() const noexcept
{
    if (pid == 0)
        return false;
    return true;
}

void Process::pWrite(int i) const
{
    fd_set set;
    struct timeval timeout;

    timeout.tv_sec = 10;
    timeout.tv_usec = 0;
    FD_ZERO(&set);
    FD_SET(writefd, &set);
    if (!select(writefd + 1, NULL, &set, NULL, &timeout))
        throw plazza::ProcessError();
    write(writefd, &i, sizeof(int));
}

void Process::pWrite(const plazza::pizza_t &i) const
{
    fd_set set;
    struct timeval timeout;

    timeout.tv_sec = pid ? 1 : 10;
    timeout.tv_usec = 0;
    FD_ZERO(&set);
    FD_SET(writefd, &set);
    if (!select(writefd + 1, NULL, &set, NULL, &timeout))
        throw plazza::ProcessError();
    write(writefd, &i, sizeof(plazza::pizza_t));
}

int Process::pKill(int sig) const noexcept
{
    if (pid)
        return kill(pid, sig);
    return -1;
}

bool Process::isDead() const noexcept
{
    if (pid)
        return waitpid(pid, NULL, WNOHANG);
    return false;
}

void Process::pWait() const noexcept
{
    int status = 0;

    if (pid) {
        while (!WIFSTOPPED(status))
            waitpid(pid, &status, WNOHANG | WUNTRACED);
        pKill(SIGCONT);
        return;
    }
    raise(SIGSTOP);
}

bool Process::canRead() const noexcept
{
    fd_set set;
    struct timeval timeout;

    FD_ZERO(&set);
    FD_SET(readfd, &set);
    timeout.tv_sec = 0;
    timeout.tv_usec = 1;
    return select(readfd + 1, &set, NULL, NULL, &timeout);
}
