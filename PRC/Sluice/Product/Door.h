#ifndef DOOR_H
#define DOOR_H

#include "iDoor.h"
#include "Enums.h"
#include "Connection.h"


    class Door : public iDoor
    {
	private:
			Connection* connection;

			Valve* lowValve;
			Valve* mediumValve;
			Valve* highValve;
			
			TrafficLight* entry;
			TrafficLight* exit;
			
			DoorSide side;
			DoorState state;
		

			
		public:
			Door(DoorSide side, Connection* c);
			virtual ~Door();
			
			virtual void OpenDoor();
			virtual void CloseDoor();
			virtual void Stop();
			
			virtual void TurnLightGreen(TrafficLight* tl);
			virtual void TurnLightRed(TrafficLight* tl);
			
			virtual void OpenValve(Valve* v);
			virtual void CloseValve(Valve* v);
			virtual void CloseAllValves();

			DoorSide GetSide()const;

			DoorState GetState();
			void SetState(DoorState ds);
			
			Valve* GetLowValve();
			Valve* GetMediumValve();
			Valve* GetHighValve();
			
			TrafficLight* GetEntry();
			TrafficLight* GetExit();
			
			Connection* GetConnection();
			
			void CheckDoorState(std::string temp);

			Door(const Door&){/*Do nothing*/}
			Door& operator=(const Door&){return *this;}
    };


#endif
