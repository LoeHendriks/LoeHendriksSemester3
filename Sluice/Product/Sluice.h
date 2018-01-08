#ifndef SLUICE_H
#define SLUICE_H

#include "Enums.h"
#include "iWaterLevel.h"
#include "Door.h"
#include "FastDoor.h"
#include "RestartDoor.h"
#include "Connection.h"


	class Sluice : public iWaterLevel
	{
	private:
			int sluiceID;
			WaterLevel heightWater;
			Door* leftDoor;
			Door* rightDoor;
			Connection* connection;
		public:
			Sluice(int sluiceID, WaterLevel heightWater, Connection* c);
			~Sluice();
			
			int GetSluiceID();
			void SetSluiceID(int sluiceID);

			Door* GetLeftDoor();
			Door* GetRightDoor();

			virtual WaterLevel GetWaterLevel();
			
			Sluice(const Sluice&){/*Do nothing*/}
			Sluice& operator=(const Sluice&){return *this;}
	};

#endif
