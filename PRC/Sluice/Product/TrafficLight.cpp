#include "TrafficLight.h"



TrafficLight::TrafficLight(DoorSide side, Connection* c)
{
	this->connection = c;
	this->side = side;
	this->red = on;
	this->green = off;
}

TrafficLight::~TrafficLight()
{

}


			
void TrafficLight::SetRed(Control c)
{
	this->red = c;
	
}
			

			
void TrafficLight::SetGreen(Control c)
{
	this->green = c;
}

Control TrafficLight::GetRed()
{
	return this->red;
}
Control TrafficLight::GetGreen()
{
	return this->green;
}

void TrafficLight::TurnRed(DoorSide doorside)
{
	if(doorside == left)
	{
		if(this->side == left)
		{
			this->connection->Command("SetTrafficLight1Green:off;");
			this->connection->Command("SetTrafficLight1Red:on;");
			
		}
		else{
			this->connection->Command("SetTrafficLight2Green:off;");
			this->connection->Command("SetTrafficLight2Red:on;");
		}
	}
	else{
		if(this->side == left)
		{
			this->connection->Command("SetTrafficLight3Green:off;");
			this->connection->Command("SetTrafficLight3Red:on;");
		}
		else{
			this->connection->Command("SetTrafficLight4Green:off;");
			this->connection->Command("SetTrafficLight4Red:on;");
		}
	}
	SetGreen(off);
	SetRed(on);
}

void TrafficLight::TurnGreen(DoorSide doorside)
{
	if(doorside == left)
	{
		if(this->side == left)
		{
			this->connection->Command("SetTrafficLight1Red:off;");
			this->connection->Command("SetTrafficLight1Green:on;");
			
		}
		else{
			this->connection->Command("SetTrafficLight2Red:off;");
			this->connection->Command("SetTrafficLight2Green:on;");
		}
	}
	else{
		if(this->side == left)
		{
			this->connection->Command("SetTrafficLight3Red:off;");
			this->connection->Command("SetTrafficLight3Green:on;");
		}
		else{
			this->connection->Command("SetTrafficLight4Red:off;");
			this->connection->Command("SetTrafficLight4Green:on;");
		}
	}
	SetRed(off);
	SetGreen(on);
}


