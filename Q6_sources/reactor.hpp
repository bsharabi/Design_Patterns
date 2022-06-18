#ifndef __REACTOR__H__
#define __REACTOR__H__
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <thread>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <poll.h>
#include "../color.hpp"
#define BUFFSIZE 1024
int portNo;
typedef int (*acceptType)(int, sockaddr *__restrict__, socklen_t *__restrict);
typedef int (*recvType)(int, void *__buf, size_t __nbytes);
socklen_t len; // store size of the address
struct sockaddr_in _svrAdd, _clntAdd;
using namespace std;

namespace re
{
    class Reactor
    {

    private:
        struct pollfd *p_fds;
        void (**handlers)();
        int fd_count;
        int fd_size;
        std::thread mThread;
        int index;
        bool stop;

    private:
        /**
         * @brief reactor constructor
         */
        Reactor();
        ~Reactor();
        /**
         * @brief running func
         */
        void run();

    public:
        void info();
    public:
        /**
         * @brief create new reactor
         */
        static void *newReactor();
        /**
         * @brief this func will get pointer to Reactor
         * pointer to some func and file descriptor
         * and will install function that will handle the output
         */
        static void InstallHandler(Reactor *, int, void (*func)());
        /**
         * @brief will get pointer to Reactor
         * and will free the handler to fd
         */
        static void RemoveHandler(Reactor *reactor);
    };

}
/**
 * @brief Initiallize the server side
 * @return int = 1 on success, 0 on failure
 */
int server(int argc, char *argv[]);
#endif //!__REACTOR__H__