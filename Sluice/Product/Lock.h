#ifndef LOCK_H
#define LOCK_H

#include "Enums.h"
//#include "DoorSide.h"
#include "Connection.h"
#include "iLock.h"




	class Lock : public iLock
	{
		private:
			LockState state;
			Control locked;
			Connection* connection;
			
		public:
			Lock(Connection* c);
			~Lock();
			
			LockState getState()const;
			void setState(LockState ls);
			
			Control getLocked()const;
			void setLocked(Control c);
			
			virtual void OpenLock(DoorSide side);
			virtual void CloseLock(DoorSide side);
			
	};
#endif
