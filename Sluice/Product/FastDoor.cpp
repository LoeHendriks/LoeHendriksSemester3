#include "FastDoor.h"
#include "Door.h"

FastDoor::FastDoor(DoorSide side, Connection* c):Door(side, c)
{
    this->lock = new Lock(c);
}

FastDoor::~FastDoor()
{
    delete this->lock;
    this->lock = NULL;
}

void FastDoor::OpenDoor()
{
    this->lock->OpenLock(this->GetSide());
    char command[100];
	sprintf(command, "SetDoor%s:open;", this->GetSide()?"Right":"Left");
	GetConnection()->Command(command);

	sprintf(command, "GetDoor%s;", this->GetSide()?"Right":"Left");
    std::string temp = GetConnection()->Command(command);
    Door::CheckDoorState(temp);
    SetState(doorOpen);
}


void FastDoor::CloseDoor()
{
    char command[100];
    sprintf(command, "GetDoor%s;", this->GetSide()?"Right":"Left");
    std::string temp = GetConnection()->Command(command);
    CheckDoorState(temp);
    if(temp == "doorLocked;")
    {
		return;
	}
	
	if(temp == "doorOpen;")
	{
		sprintf(command, "SetDoor%s:close;", this->GetSide()?"Right":"Left");
		GetConnection()->Command(command);
	}
        
	while(GetState() != doorClosed)
	{
		sprintf(command, "GetDoor%s;", this->GetSide()?"Right":"Left");
		std::string temp = GetConnection()->Command(command);
		CheckDoorState(temp);
	}
	this->lock->CloseLock(GetSide());
	SetState(doorLocked);
	return;
        
}


