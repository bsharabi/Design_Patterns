#include "singelton.hpp"

template <typename T>
T *MapFile<T>::m_instance = 0;

template <typename T>
T *MapFile<T>::Instance()
{
    if (!m_instance)
    {
        pthread_mutex_lock(&mutex);
        MapFile<T>::m_instance = new T();
    }
    pthread_mutex_unlock(&mutex);
    return m_instance;
}

template <typename T>
void MapFile<T>::destroy()
{
    pthread_mutex_lock(&mutex);

    delete MapFile<T>::m_instance;
    MapFile<T>::m_instance = 0;
    pthread_mutex_unlock(&mutex);
}
template <typename T>
MapFile<T>::MapFile() { m_instance = static_cast<T *>(this); };

template <typename T>
MapFile<T>::~MapFile(){};

int Test()
{
    int fd = -1;
    char *file_name = (char *)"./Q5_sources/fd.txt";
    YELLOW;
    cout << "open file descriptor" << endl;
    RESET;
    fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    if (-1 == fd)
    {
        printf("can not open %s", file_name);
        return -1;
    }
    GREEN;
    cout << "Get instance to mem variable with Map File singelton class" << endl;
    int **mem = Singelton::MapFile<int *>::Instance();
    RED;
    cout << "Insert to mem new object of mmap  " << endl;
    *mem = (int *)mmap(NULL, 1024, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    BLUE;
    cout << "Print address of mem" << endl;
    cout << *mem << endl;
    GREEN;
    cout << "Get instance to mem2 variable with Map File singelton class" << endl;
    BLUE;
    int **mem2 = Singelton::MapFile<int *>::Instance();
    cout << "Print address of mem2" << endl;
    cout << *mem2 << endl;
    YELLOW;
    cout << "Check if them equals" << endl;
    cout << "(mem == mem2)? -> " << ((mem == mem2) ? "True" : "False") << endl;
    cout << "(*mem == *mem2)? -> " << ((*mem == *mem2) ? "True" : "False") << endl;
    RESET;
    return 0;
}
int main(int argc, char const *argv[])
{
    system("setterm -bold on");
    cout << "________________________________ - Q5 - __________________________________" << endl;
    system("setterm -bold off");
    return Test();
}