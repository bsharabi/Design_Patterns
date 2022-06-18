#ifndef __MAIN1__H__
#define __MAIN1__H__

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <fstream>
#include <strings.h>
#include <stdlib.h>
#include <string>
#include <pthread.h>
#include <signal.h>
// #include <bits/stdc++.h>
#include <cstdlib>
#include <thread>
#include <cmath>
#include "./Q1-3_sources/queue.hpp"
#include "./Q1-3_sources/active_object.hpp"
#include "color.hpp"
using namespace active;
#define em 5

#define BUFFSIZE 1024
p_queue q1;
int size = 0;
int listenFd;
int noThread = 0;
int count = 0;
pthread_t threadA[100];
int pId, portNo;
socklen_t len; // store size of the address
struct sockaddr_in svrAdd, clntAdd;

/**
 * @brief The functions welcome,red,yellow,blue,green and reset are just for fun
 * We want you to enjoy the proccess :)
 */
void welcome()
{
    printf("\033[1;31m    $$      $$$$$  $$$$$$$$$ $     $         \033[1;34m $$$$$         $$     $$$$$       $$      $  $    \n");
    printf("\033[1;31m   $  $     $   $      $      $   $          \033[1;34m $   $        $  $    $   $      $  $     $ $    \n");
    printf("\033[1;31m  $ -- $    $$$$$      $        $    \033[1;33m @@@@@@ \033[1;34m $$$$$$$     $ -- $   $$$$$     $ -- $    $$        \n");
    printf("\033[1;31m $      $   $    $     $        $            \033[1;34m $     $    $      $  $    $   $      $   $ $         \n");
    printf("\033[1;31m$        $  $     $    $        $            \033[1;34m $$$$$$$   $        $ $     $ $        $  $  $       \n");
}

/**
 * @brief
 *
 * @param signum : number's signal
 * @return non.
 */
void sig_handler(int);

/**
 * @brief Connecting the client inputes : push/pop/top
 * Checking if the input is valid
 * If no -> throiwng an error
 * If yes -> dealing with the input in the needed way
 * @return void* 
 */
void *task1(void *);

/**
 * @brief Initiallize the server side
 * @return int = 1 on success, 0 on failure
 */
int server(int argc, char *argv[]);
#endif  //!__MAIN1__H__