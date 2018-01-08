#include "RestartDoor.h"
#include "Door.h"


RestartDoor::RestartDoor(DoorSide side, Connection* c):Door(side, c)
{
    
}

RestartDoor::~RestartDoor()
{

}

void RestartDoor::OpenDoor()
{
    while(GetState() != doorOpen)
    {
        char command[100];
	    sprintf(command, "SetDoor%s:open;", this->GetSide()?"Right":"Left");
	    GetConnection()->Command(command);

	    sprintf(command, "GetDoor%s;", this->GetSide()?"Right":"Left");
        std::string temp = GetConnection()->Command(command);
	    Door::CheckDoorState(temp);
    }
}
    
void RestartDoor::CloseDoor()
{
    while(GetState() != doorClosed)
    {
        char command[100];
        sprintf(command, "SetDoor%s:close;", this->GetSide()?"Right":"Left");
        GetConnection()->Command(command);

        sprintf(command, "GetDoor%s;", this->GetSide()?"Right":"Left");
        std::string temp = GetConnection()->Command(command);
        CheckDoorState(temp);
        
    }
}
    
