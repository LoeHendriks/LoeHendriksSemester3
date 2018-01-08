#ifndef FASTDOOR_H
#define FASTDOOR_H

#include "Door.h"
#include "Lock.h"


class FastDoor : public Door
{
	private:
		Lock* lock;
		int closingCheck;
	public:
		FastDoor(DoorSide side, Connection* c);
		~FastDoor();
		
		virtual void OpenDoor();
		virtual void CloseDoor();
		
};





#endif
