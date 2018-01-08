#ifndef RESTARTDOOR_H
#define RESTARTDOOR_H

#include "Door.h"


	class RestartDoor : public Door
	{
		private:
			
		public:
			RestartDoor(DoorSide side, Connection* c);
			~RestartDoor();
			
			virtual void OpenDoor();
			virtual void CloseDoor();
					
	};


#endif
