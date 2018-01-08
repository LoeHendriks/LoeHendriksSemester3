#ifndef ITRAFFICLIGHT_H
#define ITRAFFICLIGHT_H

#include "Enums.h"
    class iTrafficLight
    {
        public:
			virtual ~iTrafficLight() {};
			virtual void TurnRed(DoorSide side)= 0;
            virtual void TurnGreen(DoorSide side) = 0;
    };


#endif
