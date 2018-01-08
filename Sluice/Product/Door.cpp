#include "Door.h"
#include <string>



Door::Door(DoorSide side, Connection* c)
{
	this->connection = c;
	this->side = side;
	this->state = doorClosed;
	this->lowValve = new Valve(c, 1);
	this->mediumValve = new Valve(c, 2);
	this->highValve = new Valve(c, 3);

	if(this->side == left)
	{
		this->entry = new TrafficLight(left, c);
		this->exit = new TrafficLight(right, c);
	}
	else if(this->side == right)
	{
		this->entry = new TrafficLight(right, c);
		this->exit = new TrafficLight(left, c);
	}
	
}
			
Door::~Door()
{
	delete this->lowValve;
	this->lowValve = NULL;
	delete this->mediumValve;
	this->mediumValve = NULL;
	delete this->highValve;
	this->highValve = NULL;
	delete this->entry;
	this->entry = NULL;
	delete this->exit;
	this->exit = NULL;
}

void Door::OpenDoor()
{
	char command[100];
	sprintf(command, "SetDoor%s:open;", this->GetSide()?"Right":"Left");
	this->connection->Command(command);
}

void Door::CloseDoor()
{
	char command[100];
	sprintf(command, "SetDoor%s:close;", this->GetSide()?"Right":"Left");
	this->connection->Command(command);
}

void Door::Stop()
{
	char command[100];
	sprintf(command, "SetDoor%s:stop;", this->GetSide()?"Right":"Left");
	this->connection->Command(command);

	sprintf(command, "GetDoor%s;", this->GetSide()?"Right":"Left");
	std::string temp = this->connection->Command(command);
	CheckDoorState(temp);
}
			
void Door::TurnLightGreen(TrafficLight* tl)
{
	tl->TurnGreen(side);
}

void Door::TurnLightRed(TrafficLight* tl)
{
	tl->TurnRed(side);
}

void Door::OpenValve(Valve* v)
{
	v->OpenValve(this->side);
}

void Door::CloseValve(Valve* v)
{
	v->CloseValve(this->side);
}

void Door::CloseAllValves()
{
	this->lowValve->CloseValve(this->side);
	this->mediumValve->CloseValve(this->side);
	this->highValve->CloseValve(this->side);
}
			
DoorSide Door::GetSide()const
{
	return this->side;
}




DoorState Door::GetState()
{
	char command[100];
	sprintf(command, "GetDoor%s;", this->GetSide()?"Right":"Left");
	std::string temp = this->connection->Command(command);
	CheckDoorState(temp);
	return this->state;
}

void Door::SetState(DoorState ds)
{
	this->state = ds;
}



Valve* Door::GetLowValve()
{
	return this->lowValve;
}
			
Valve* Door::GetMediumValve()
{
	return this->mediumValve;
}
			
Valve* Door::GetHighValve()
{
	return this->highValve;
}

TrafficLight* Door::GetEntry()
{
	return this->entry;
}
			
TrafficLight* Door::GetExit()
{
	return this->exit;
}

Connection* Door::GetConnection()
{
	return this->connection;
}



void Door::CheckDoorState(std::string temp)
{
		if(temp == "doorLocked;")
		{
			SetState(doorLocked);
		}
		else if(temp == "doorClosed;")
		{
			SetState(doorClosed);
		}
		else if(temp == "doorOpen;")
		{
			SetState(doorOpen);
		}
		else if(temp == "doorClosing;")
		{
			SetState(doorClosing);
		}
		else if(temp == "doorOpening;")
		{
			SetState(doorOpening);
		}
		else if(temp == "doorStopped;")
		{
			SetState(doorStopped);
		}
		else if(temp == "motorDamage;")
		{
			SetState(motorDamage);
		}
}