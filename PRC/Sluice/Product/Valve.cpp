#include "Valve.h"



Valve::Valve(Connection* c, int valveID)
{
	this->status = closed;
	this->connection = c;
	this->valveID = valveID;
}

Valve::~Valve()
{

}

ValveStatus Valve::GetStatus()const
{
	return this->status;
}

void Valve::SetStatus(ValveStatus vs)
{
	this->status = vs;
}

void Valve::OpenValve(DoorSide side)
{

	char command[100];
	sprintf(command, "SetDoor%sValve%d:open;", side?"Right":"Left", this->valveID);
	this->connection->Command(command);
	SetStatus(open);
}

void Valve::CloseValve(DoorSide side)
{
	char command[100];
	sprintf(command, "SetDoor%sValve%d:close;", side?"Right":"Left", this->valveID);
	this->connection->Command(command);
	SetStatus(closed);
}
