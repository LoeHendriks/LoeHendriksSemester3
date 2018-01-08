#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "iTrafficLight.h"
#include "Enums.h"
//#include "DoorSide.h"
#include "Connection.h"


    class TrafficLight : public iTrafficLight
    {
        private:
			Control red;
			Control green;
			DoorSide side;
			Connection* connection;
		public:
			TrafficLight(DoorSide side, Connection* c);
			~TrafficLight();
			Control GetRed();
			Control GetGreen();
			void SetRed(Control c);
			void SetGreen(Control c);
			
			virtual void TurnRed(DoorSide doorside);
			virtual void TurnGreen(DoorSide doorside);
			
    };


#endif
