#ifndef XBOX_T_H
#define XBOX_T_H


#include <semaphore.h>

struct xbox_t {
    unsigned char data[20];
    sem_t sem1;
    sem_t sem2;
};

#endif