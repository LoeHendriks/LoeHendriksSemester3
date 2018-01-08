#ifndef XBOX_T_H
#define XBOX_T_H


#include <semaphore.h>

struct xbox_t {
    //unsigned char data[20];
    int32_t dpadLeft;
    int32_t dpadRight;
    int32_t dpadUp;
    int32_t dpadDown;
    int32_t start;
    int32_t back;
    int32_t xbox;
    int32_t a;
    int32_t b;
    int32_t x;
    int32_t y;
    int32_t rb;
    int32_t lb;
    int32_t leftJoystick;
    int32_t rightJoystick;
    //int dpad;
    sem_t sem1;
    //sem_t sem2;
};

#endif