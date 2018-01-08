#ifndef VALVE_H
#define VALVE_H

#include "iValve.h"
#include "Enums.h"
#include "Connection.h"


    class Valve : public iValve
    {
        private:
			ValveStatus status;
			Connection* connection;
			int valveID;
			
		public:
			Valve(Connection* c, int valveID);
			virtual ~Valve();
			
			virtual void OpenValve(DoorSide side);
			virtual void CloseValve(DoorSide side);
			
			ValveStatus GetStatus()const;
			void SetStatus(ValveStatus vs);
    };


#endif
