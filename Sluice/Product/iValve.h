#ifndef IVALVE_H
#define IVALVE_H

#include "Enums.h"

    class iValve
    {
        public:
			virtual ~iValve() {};
			virtual void OpenValve(DoorSide side)= 0;
			virtual void CloseValve(DoorSide side) = 0;
    };


#endif
