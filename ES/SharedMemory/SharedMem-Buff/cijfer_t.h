#ifndef CIJFER_T_H
#define CIJFER_T_H

#include <semaphore.h>

struct cijfer_t {
	int waarde;
    char uitspraak[6];
    sem_t semaphore;
};

#endif