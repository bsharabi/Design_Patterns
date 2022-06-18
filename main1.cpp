#include "main1.hpp"
int server(int argc, char *argv[])
{

    if (argc >= 2)
    {
        try
        {
            portNo = atoi(argv[1]);
            if ((portNo > 65535) || (portNo < 2000))
            {
                throw std::invalid_argument("Please enter a port number between 2000 - 65535");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            portNo = htons(3003);
        }
    }
    else
    {
        portNo = htons(3003);
    }
    std::cout << "Port :" << portNo << std::endl;

    // create socket
    listenFd = socket(AF_INET, SOCK_STREAM, 0);

    if (listenFd < 0)
    {
        std::cerr << "Cannot open socket" << std::endl;
        return listenFd;
    }

    bzero((char *)&svrAdd, sizeof(svrAdd));

    svrAdd.sin_family = AF_INET;
    svrAdd.sin_addr.s_addr = INADDR_ANY;
    svrAdd.sin_port = htons(portNo);

    // bind socket
    if (bind(listenFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd)) < 0)
    {
        std::cerr << "Cannot bind" << std::endl;
        return 0;
    }

    if (listen(listenFd, 5) == -1)
    {
        printf("\n listen has failed\n");
        return 0;
    }

    return listenFd;
}
void sig_handler(int signum)
{
    destroyQ(q1);
    switch (signum)
    {
    case SIGTSTP:
        RED;
        puts("");
        printf("Trying to exit on CONTROL-Z command\n");
    case SIGINT:
        YELLOW;
        printf("Trying to exit on CONTROL-C command\n");
    case SIGQUIT:
        GREEN;
        printf("Trying to exit on CONTROL-/ command\n");
    default:
        close(listenFd);
        std::cout << "Closing Server" << std::endl;
    }
}
void *task1(void *dummyPt)
{
    int sock = *((int *)dummyPt);
    int numberThread = *((int *)dummyPt + 1);
    std::cout << "Thread No: " << pthread_self() << " Socket No " << sock << " NumberThread " << numberThread << std::endl;

    while (true)
    {
        char *writer = 0;
        char reader[BUFFSIZE] = {0};
        bzero(reader, BUFFSIZE);
        if (read(sock, reader, BUFFSIZE) == -1)
        {
            puts("error");
        }
        if (strncmp(reader, "PUSH", 4) == 0)
        {
            puts("Pushed");
            p_value value = (p_value)malloc(sizeof(value));
            strcpy(value->str, reader + 5);
            value->sock = sock;
            enQ(value, q1);
        }
        else if (strncmp(reader, "EXIT", 4) == 0)
        {
            write(sock, "succ", 4);
            close(sock);
            std::cout << "\nClosing thread and connection" << std::endl;
            break;
        }
        else
        {
            write(sock, "(-1)", 4);
        }
    }
    return 0;
}
void *task2(void *a)
{
    p_queue q = (p_queue)a;
    BLUE;
    cout << "Thread number - " << pthread_self() << " is working!\n";
    RESET;
    sleep(1);
    enQ((void *)"1", q);
    enQ((void *)"2", q);
    enQ((void *)"3", q);
    enQ((void *)"4", q);
    enQ((void *)"5", q);
    return 0;
}
void simulation_Queue()
{
    p_queue q = createQ();
    q->id = 1;
    pthread_t thread1[2];
    void *arg = {q};
    pthread_create(&thread1[0], NULL, task2, arg);

    pthread_create(&thread1[1], NULL, task2, arg);
    cout << "Try to Dequeue" << endl;
    printf("1. %c \n", *((char *)deQ(q)));
    printf("2. %c \n", *((char *)deQ(q)));
    printf("3. %c \n", *((char *)deQ(q)));

    pthread_join(thread1[0], NULL);
    pthread_join(thread1[1], NULL);
}
void simulation_ActiveObject()
{
    p_queue q1 = createQ();
    q1->id = 1;
    enQ(nullptr, q1);
    activeObject *ao1 = activeObject::newAO(q1, func1, func2);
    sleep(2);
    p_value v = (p_value)malloc(sizeof(value));
    v->sock = 2;
    strcpy(v->str, "Try");
    enQ(v, q1);
    sleep(3);
}
void simulation_ActiveObject_PipeLine(int argc, char *argv[])
{
    // Init new Q
    q1 = createQ();
    p_queue q2 = createQ();
    p_queue q3 = createQ();
    // Set name's Q
    q1->id = 1;
    q2->id = 2;
    q3->id = 3;

    enQ(q2, q1);
    enQ(q3, q2);
    enQ(nullptr, q3);

    activeObject *ao1 = activeObject::newAO(q1, ceasar_cipher, enQ);
    activeObject *ao2 = activeObject::newAO(q2, transform, enQ);
    activeObject *ao3 = activeObject::newAO(q3, sendRes, nullptr);

    RED;
    welcome();
    RESET;
    signal(SIGINT, sig_handler);
    signal(SIGTSTP, sig_handler);
    signal(SIGQUIT, sig_handler);

    sleep(1);
    if (server(argc, argv) < 0)
        return;
    sleep(1);
    cout << "Open another terminal and run the command ";
    YELLOW;
    cout << "make client" << endl;
    RESET;
    cout << "Now run the command";
    YELLOW;
    cout << " ./client " << portNo << endl;
    RESET;
    cout << "How to use the programm from client: " << endl;

    cout << "PUSH [your input] : inserting element into the queue " << endl;
    cout << "EXIT : To proceed to the next test should be sent from the client EXIT" << endl;

    std::cout << "Listening" << std::endl;
    socklen_t len = sizeof(clntAdd);
    // this is where client connects. svr will hang in this mode until client conn
    int connFd = accept(listenFd, (struct sockaddr *)&clntAdd, &len);

    if (connFd < 0)
    {
        std::cerr << "Cannot accept connection" << std::endl;
        return;
    }
    else
    {
        std::cout << "Connection successful" << std::endl;
    }
    int a[]{connFd, 0};
    int error = pthread_create(&threadA[0], NULL, task1, (void *)&a);
    if (error != 0)
        printf("\nThread can't be created :[%s]",
               strerror(error));

    pthread_join(threadA[0], NULL);

    if (q1->size != 0)
        destroyQ(q1);

    activeObject::destroyAO(ao1);
    activeObject::destroyAO(ao2);
    activeObject::destroyAO(ao3);
}
int main(int argc, char *argv[])
{
    // Q1
    system("setterm -bold on");
    cout << "________________________________ - Q1 - __________________________________" << endl;
    system("setterm -bold off");
    simulation_Queue();
    cout << "------ End -------" << endl;
    // // Q2
    system("setterm -bold on");
    cout << "________________________________ - Q2 - __________________________________" << endl;
    system("setterm -bold off");
    simulation_ActiveObject();
    cout << "------ End -------" << endl;
    // // Q3
    system("setterm -bold on");
    cout << "________________________________- Q3 - __________________________________" << endl;
    system("setterm -bold off");
    simulation_ActiveObject_PipeLine(argc, argv);
    cout << "------ End -------" << endl;

    return 0;
}
