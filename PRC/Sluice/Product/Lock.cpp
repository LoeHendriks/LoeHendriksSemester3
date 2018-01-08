#include "Lock.h"


Lock::Lock(Connection* c)
{
	this->state = lockWorking;
	this->locked = on;
	this->connection = c;
}

Lock::~Lock()
{
	
}

LockState Lock::getState()const
{
	return this->state;
}

void Lock::setState(LockState ls)
{
	this->state = ls;
}

Control Lock::getLocked()const
{
	return this->locked;
}

void Lock::setLocked(Control c)
{
	this->locked = c;
}

void Lock::OpenLock(DoorSide side)
{
	if(side == left)
	{
		this->connection->Command("SetDoorLockLeft:off;");
		
	}
	else if(side == right)
	{
		this->connection->Command("SetDoorLockRight:off;");
		
	}
}
	
void Lock::CloseLock(DoorSide side)
{
	if(side == left)
	{
		this->connection->Command("SetDoorLockLeft:on;");

	}
	else if(side == right)
	{
		this->connection->Command("SetDoorLockRight:on;");
		
	}
}


