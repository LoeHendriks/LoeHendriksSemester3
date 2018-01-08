#ifndef CIJFERBUFFER_T_H
#define CIJFERBUFFER_T_H

#include <semaphore.h>
#include "cijfer_t.h"

struct cijferBuffer_t {

	struct cijfer_t buffer[10];
    sem_t sem;
    sem_t sem2;
};

#endif