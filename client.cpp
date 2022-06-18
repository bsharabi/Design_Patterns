#include "client.hpp"
void red()
{
    printf("\033[1;31m");
}
void yellow()
{
    printf("\033[1;33m");
}
void reset()
{
    printf("\033[0m");
}
void blue()
{
    printf("\033[0;34m");
}
void green()
{
    printf("\033[0;32m");
}
void welcom()
{
    green();
    puts(" =============================================");
    printf("\033[0;32m||\033[1;36m   $$$$  $     $  $$$$  $$   $ $$$$$$$$$$\033[0;32m ||\n");
    printf("||\033[1;36m  $      $     $  $     $ $  $     $     \033[0;32m ||\n");
    printf("||\033[1;36m  $      $     $  $$$$  $  $ $     $     \033[0;32m ||\n");
    printf("||\033[1;36m  $      $     $  $     $   $$     $     \033[0;32m ||\n");
    printf("||\033[1;36m   $$$$  $$$$  $  $$$$  $    $     $     \033[0;32m ||\n");
    puts(" =============================================");
}
void sig_handler(int signum)
{
    switch (signum)
    {
    case SIGTSTP:
        red();
        puts("");
        printf("Trying to exit on CONTROL-Z command\n");
    case SIGINT:
        yellow();
        printf("Trying to exit on CONTROL-C command \n");
    case SIGQUIT:
        green();
        printf("Trying to exit on CONTROL-/ command\n");
    default:
        reset();
        close(sockFd);
        exit(1);
        cout << "Closing socket" << endl;
    }
}
int client(int argc, char *argv[])
{
    red();
    int portNo;
    bool loop = false;
    struct sockaddr_in svrAdd;
    struct hostent *server;

    if (argc >= 2)
    {
        try
        {
            portNo = atoi(argv[1]);
            if ((portNo > 65535) || (portNo < 2000))
            {
                throw invalid_argument("Please enter a port number between 2000 - 65535");
            }
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            portNo = htons(3003);
            cout << "Port :" << portNo << endl;
        }
    }
    else
    {
        portNo = htons(3003);
        cout << "Port :" << portNo << endl;
    }

    sockFd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockFd < 0)
    {
        cerr << "Cannot open socket" << endl;
        return 0;
    }

    server = gethostbyname("localhost");

    if (server == NULL)
    {
        cerr << "Host does not exist" << endl;
        return 0;
    }

    bzero((char *)&svrAdd, sizeof(svrAdd));
    svrAdd.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&svrAdd.sin_addr.s_addr, (size_t)server->h_length);

    svrAdd.sin_port = htons(portNo);

    int checker = connect(sockFd, (struct sockaddr *)&svrAdd, sizeof(svrAdd));

    if (checker < 0)
    {
        cerr << "Cannot connect!" << endl;
        return 0;
    }
    return 1;
}
void *task(void *args)
{
    while (stop)
    {
        bzero(reader, BUFFSIZE);
        read(sockFd, reader, BUFFSIZE);
        red();
        if (strcmp(reader, "EXIT") == 0)
        {
            close(sockFd);
            exit(1);
        }
        if (strcmp(reader, "(-1)") == 0)
            printf("\nERROR: Invaild commands\n");
        else
            printf("\nOUTPUT: ");
        puts(reader);
        mc++;
        reset();
    }
    return 0;
}
int main(int argc, char *argv[])
{
    welcom();
    signal(SIGINT, sig_handler);
    signal(SIGTSTP, sig_handler);
    signal(SIGQUIT, sig_handler);
    mc = 0;
    stop = 1;
    if (!client(argc, argv))
        return 0;
    pthread_t recvThread;
    pthread_create(&recvThread, NULL, task, NULL);
    for (;;)
    {
        yellow();
        sleep(1);
        cout << "Enter stuff: ";
        blue();
        bzero(wirter, BUFFSIZE);
        cin.getline(wirter, BUFFSIZE);
        write(sockFd, wirter, strlen(wirter));
        string exit(wirter);
        if (exit == "EXIT")
        {
            close(sockFd);
            red();
            cout << "Try to close client" << endl;
            stop = 0;
            break;
        }
    }
    pthread_join(recvThread, NULL);
    return 1;
}