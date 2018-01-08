#ifndef IDOOR_H
#define IDOOR_H

#include "TrafficLight.h"
#include "Valve.h"


    class iDoor
    {
        public:
			virtual ~iDoor() {};
			virtual void OpenDoor()= 0;
			virtual void CloseDoor() = 0;
			virtual void Stop() = 0;
			virtual void TurnLightGreen(TrafficLight* tl) = 0;//
			virtual void TurnLightRed(TrafficLight* tl) = 0;//
			virtual void OpenValve(Valve* v) = 0;
			virtual void CloseValve(Valve* v) = 0;
			virtual void CloseAllValves() = 0;
    };


#endif
