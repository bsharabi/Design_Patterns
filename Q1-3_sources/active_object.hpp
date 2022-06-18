#ifndef __OBJECT__
#define __OBJECT__
#include "queue.hpp"
#include "../color.hpp"
#include <string.h>
#include <string>
#include <iostream>
#include <thread>
#include <netdb.h>

using namespace std;

namespace active
{
    class activeObject
    {
    private:
        void *(*s_func1)(void *);
        void *(*e_func2)(void *, p_queue);
        p_queue _q;
        p_queue next_q;
        std::thread mThread;
        int stop;
        /**
         * @brief This function will get some string
         * trasform capital letters to small
         * and small letters to capital
         * @param str: given string to check
         */
        void Run();
        /**
         * @brief This function will get some string
         * trasform capital letters to small
         * and small letters to capital
         * @param str: given string to check
         */
        activeObject(struct queue *q, void *(*func1)(void *), void *(*func2)(void *, p_queue));
        /**
         * @brief This function will get some string
         * trasform capital letters to small
         * and small letters to capital
         * @param str: given string to check
         */
        ~activeObject();

    public:
        //------------------------- Constructor -----------------------------
        /**
         * @brief This function will get some string
         * trasform capital letters to small
         * and small letters to capital
         * @param str: given string to check
         */
        static activeObject *newAO(struct queue *q, void *(*func1)(void *), void *(*func2)(void *, p_queue));
        /**
         * @brief This function will get some string
         * trasform capital letters to small
         * and small letters to capital
         * @param str: given string to check
         */
        static void destroyAO(activeObject *ao);
    };

    /**
     * @brief This function will get some string
     * and will activate ceasar cipher on int by key value : 1
     * if the original letter was capital it will remain capital
     * check if the string have only english letters
     * if not return
     * @param str: given string to encrypt
     */
    void *ceasar_cipher(void *str);

    /**
     * @brief This function will get some string
     * trasform capital letters to small
     * and small letters to capital
     * @param str: given string to check
     */
    void *transform(void *str);

    /**
     * @brief This func will send the finished processed string to the client
     */
    void *sendRes(void *node);
    /**
     * @brief simple print func
     */
    void *func1(void *node);
    /**
     * @brief simple print func
     */
    void *func2(void *node, p_queue);
}
#endif