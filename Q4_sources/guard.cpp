#include "guard.hpp"

/*
NO
it's not possible to protect strtok by using guard because when thread is entering the function not in the right order
it can make the output wrong and not as expected
*/
namespace design
{
    guard::guard()
    {
        pthread_mutex_lock(&mtx_lock);
        GREEN;
        cout << "Initializing guard and mutex lock" << std::endl;
    }

    guard::~guard()
    {
        pthread_mutex_unlock(&mtx_lock);
        RED;
        cout << "Destroying guard and unlocking mutex" << std::endl;
    }
}

void *task_guard(void *args)
{
    guard guard{};
    sleep(2);
    BLUE;
    std::cout << "Global pointer before change: " << global_ptr << std::endl;
    int local_ptr;
    global_ptr = &local_ptr;
    YELLOW;
    std::cout << "Global pointer after change: " << global_ptr << std::endl;
    return NULL;
}
int guard_Test()
{
    pthread_mutex_init(&mtx_lock, NULL);
    pthread_t threads[4];
    int a = 5;
    for (int i = 0; i < 4; i++)
    {
        pthread_create(&threads[i], NULL, &task_guard, &i);
    }
    for (int i = 0; i < 4; i++)
    {
        pthread_join(threads[i], NULL);
    }
    CYAN;
    std::cout << "Finished :)" << std::endl;
    RESET;
    return 0;
}
int main()
{
    system("setterm -bold on");
    cout << "________________________________ - Q4 - __________________________________" << endl;
    system("setterm -bold off");
    return guard_Test();
}