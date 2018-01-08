#ifndef ADMINISTRATION_H
#define ADMINISTRATION_H

#include <string>
#include <vector>
#include "Sluice.h"
#include "Enums.h"



	class Administration{
		private:
			std::vector<Sluice*> sluiceList;
			Sluice* GetSluiceFromList(int ID);
			int alarmCheck; 
			int threadcheck;
			int threadend;

		public:
			Administration();
			~Administration();
			 
			bool Add(Sluice* s);
			std::vector<Sluice*> GetSluiceList();
			void Start(int sluiceID);
			void FreeEntry(int sluiceID);
			void FreeExit(int sluiceID);
			void Alarm(int sluiceID, DoorSide side);
			void Recover(int sluiceID, DoorSide side);
			
	};

#endif
