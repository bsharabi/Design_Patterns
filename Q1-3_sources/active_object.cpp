#include "active_object.hpp"

namespace active
{

    void *func1(void *node)
    {
        BLUE;
        printf("Doing something on every active object\n");
        RESET;
        return 0;
    }
    void *func2(void *node, p_queue q)
    {
        YELLOW;
        printf("Doing something at the end\n");
        RESET;
        return 0;
    }
    void *ceasar_cipher(void *node)
    {
        char *str = ((p_value)node)->str;
        int len = strlen(str);
        if (len < 1)
        {
            printf("please enter valid string\n");
            throw invalid_argument("please enter valid string\n");
        }

        for (int i = 0; i < len; i++)
        {
            if (str[i] < 65 || (str[i] > 90 && str[i] < 97) || str[i] > 122)
            {
                printf("enter valid string between a-z||A-Z\n");
                throw invalid_argument("enter valid string between a-z||A-Z\n");
            }

            if (str[i] == 'Z')
            {
                str[i] = 'A';
            }

            if (str[i] == 'z')
            {
                str[i] = 'a';
            }

            else
            {
                str[i] += 1;
            }
        }
        return 0;
    }
    void *transform(void *node)
    {
        char *str = ((p_value)node)->str;
        int len = strlen(str);
        if (len < 1)
        {
            printf("please enter valid string\n");
            throw invalid_argument("please enter valid string\n");
        }

        for (int i = 0; i < len; i++)
        {
            // A..Z
            if (str[i] >= 65 && str[i] <= 90)
            {
                str[i] = str[i] + 32;
            }
            // a..z
            else if (str[i] >= 97 && str[i] <= 122)
            {
                str[i] = str[i] - 32;
            }

            else
            {
                printf("enter valid string between a-z||A-Z\n");
                throw invalid_argument("enter valid string between a-z||A-Z\n");
            }
        }
        return 0;
    }
    void *sendRes(void *node)
    {
        p_value temp = (p_value)node;
        int fd = temp->sock;
        char *str = temp->str;
        send(fd, str, strlen(str), 0);
        return 0;
    }
    activeObject *activeObject::newAO(struct queue *q, void *(*func1)(void *), void *(*func2)(void *, p_queue))
    {
        return new activeObject(q, func1, func2);
    }
    void activeObject::destroyAO(activeObject *ao)
    {
        RED;
        printf("Trying to destroy active object number %d\n", ao->_q->id);
        destroyQ(ao->_q);
        GREEN;
        ao->stop = 0;
        printf("Active object has been destroyed\n");
    }
    activeObject::~activeObject()
    {
        if (mThread.joinable())
        {
            mThread.join();
        }
    }
    activeObject::activeObject(struct queue *q, void *(*func1)(void *), void *(*func2)(void *, p_queue))
    {
        sleep(1);
        s_func1 = func1;
        e_func2 = func2;
        _q = q;
        next_q = (p_queue)deQ(_q);
        stop = 1;
        mThread = std::thread(&activeObject::Run, this);
        mThread.detach();
    }
    void activeObject::Run()
    {
        while (true)
        {
            RED;
            cout << "Number ActiveObject - " << _q->id << endl;
            RESET;
            p_value value = (p_value)deQ(_q);
            try
            {
                s_func1(value);
            }
            catch (...)
            {
                cout << "invaild argument - " << value->str << endl;
                send(value->sock, "ERR", 3, 0);
                 if (value)
                        free(value);
                continue;
            }

            cout << "After first function in ActiveObject  " << _q->id << endl;
            if (e_func2 != nullptr)
            {
                if (next_q != nullptr)
                {
                    cout << "Try to pass to next ActiveObject number " << next_q->id << endl;
                }
                try
                {
                    e_func2(value, next_q);
                }
                catch (...)
                {
                    cout << "invaild argument - " << value->str << endl;
                    send(value->sock, "ERR", 3, 0);
                    if (value)
                        free(value);
                    continue;
                }
            }
            else
            {
                YELLOW;
                cout << "The answer was sent to the client successfully, having passed three active Object" << endl;
                cout << "fd socket - " << value->sock << endl;
                cout << "new string - " << value->str << endl;
                 if (value)
                        free(value);
                RESET;
            }
            cout << "After second function in ActiveObject  " << _q->id << endl;
        }
    }

} // namespace active
