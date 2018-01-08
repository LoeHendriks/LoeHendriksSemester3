#ifndef ILOCK_H
#define ILOCK_H

#include "Enums.h"

    class iLock
    {
        public:
			virtual ~iLock() {};
			virtual void OpenLock(DoorSide side)= 0;
			virtual void CloseLock(DoorSide side) = 0;
    };


#endif
