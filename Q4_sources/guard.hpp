#ifndef __GUARD__H__
#define __GUARD__H__

#include <pthread.h>
#include <iostream>
#include <mutex>
#include <string.h>
#include <thread>
#include <stdio.h>
#include <unistd.h>
#include "../color.hpp"
using namespace std;
void *global_ptr; // global pointer
pthread_mutex_t mtx_lock;
void *task_guard(void *args);
int guard_Test();
namespace design
{
    class guard
    {
    public:
        guard();
        ~guard();
    };
}
using namespace design;
#endif //!__GUARD__H__