#include "Administration.h"
#include <iostream>
#include <stdio.h>
#include <pthread.h>


Administration::Administration()
{


}

Administration::~Administration()
{
	for(unsigned int i = 0; i < sluiceList.size();i++)
	{
		delete sluiceList[i];
		sluiceList[i] = NULL;
	}
}


static void *
myThread (void * threadArgs)
{
   char choice = '\0';
   while(1)
   {
		std::cin >> choice;
		std::cin.ignore();
		if(choice == '4')
		{
			int* checkPtr = (int*)threadArgs;
			*checkPtr = 1;
		}
		else if(choice == '5')
		{
			int* checkPtr = (int*)threadArgs;
			*checkPtr = 2;
		}
		else{
		
			pthread_exit(0);
			
		}
	}
}

void Administration::Start(int sluiceID)
{
	pthread_t   threadID;
	if(threadcheck != 1)
	{
		if(pthread_create(&threadID, NULL, myThread, &alarmCheck) != 0)
		{
			std::cout << "Error cant create thread" << std::endl;
		}
		this->threadcheck = 1;
	}

	Sluice* sluice = GetSluiceFromList(sluiceID);
	int lowcheck = 1;
	int mediumCheck = 1;
	int highCheck = 1;
    if(sluice->GetWaterLevel() == low)
    {
		sluice->GetLeftDoor()->TurnLightRed(sluice->GetLeftDoor()->GetEntry());
		sluice->GetLeftDoor()->TurnLightRed(sluice->GetLeftDoor()->GetExit());
		sluice->GetLeftDoor()->CloseDoor();
		if(alarmCheck == 1)
		{
			Alarm(sluiceID, left);
			while(alarmCheck == 1){}
		}
      	while(sluice->GetLeftDoor()->GetState() == doorClosed || sluice->GetLeftDoor()->GetState() == doorLocked)
     	{
			if(alarmCheck == 1)
			{
				Alarm(sluiceID, right);
				while(alarmCheck == 1){}
			}
			if(sluice->GetWaterLevel() == low && lowcheck == 1)
			{
				sluice->GetRightDoor()->OpenValve(sluice->GetRightDoor()->GetLowValve());
				lowcheck = 0;
			}
			
			if(sluice->GetWaterLevel() == aboveValve2 && mediumCheck == 1)
			{
				sluice->GetRightDoor()->OpenValve(sluice->GetRightDoor()->GetMediumValve());
				mediumCheck = 0;
			}
			if(sluice->GetWaterLevel() == aboveValve3 && highCheck == 1)
			{
				sluice->GetRightDoor()->OpenValve(sluice->GetRightDoor()->GetHighValve());
				highCheck = 0;
			}
			if(sluice->GetWaterLevel() == high)
			{
				sluice->GetRightDoor()->CloseAllValves();
				sluice->GetRightDoor()->OpenDoor();
				while(sluice->GetRightDoor()->GetState() != doorOpen)
				{
					if(alarmCheck == 1)
					{
						Alarm(sluiceID, right);
						while(alarmCheck == 1){}
						Recover(sluiceID, right);
					}
				}
				pthread_cancel(threadID);
				pthread_detach(threadID);
				threadcheck = 0;
			return;
        }
      }
      Start(sluiceID);
    }
    else if(sluice->GetWaterLevel() == high)
    {
		sluice->GetRightDoor()->TurnLightRed(sluice->GetRightDoor()->GetEntry());
		sluice->GetRightDoor()->TurnLightRed(sluice->GetRightDoor()->GetExit());
		sluice->GetRightDoor()->CloseDoor();
		if(alarmCheck == 1)
		{
			Alarm(sluiceID, right);
			while(alarmCheck == 1){}
		}

    	while(sluice->GetRightDoor()->GetState() == doorClosed || sluice->GetRightDoor()->GetState() == doorLocked)
    	{
			if(alarmCheck == 1)
			{
				Alarm(sluiceID, left);
				while(alarmCheck == 1){}
			}
    		sluice->GetLeftDoor()->OpenValve(sluice->GetLeftDoor()->GetLowValve());
			if(sluice->GetWaterLevel() == low)
			{
				sluice->GetLeftDoor()->CloseValve(sluice->GetLeftDoor()->GetLowValve());
				sluice->GetLeftDoor()->OpenDoor();
				while(sluice->GetLeftDoor()->GetState() != doorOpen)
				{
					if(alarmCheck == 1)
					{
						Alarm(sluiceID, left);
						while(alarmCheck == 1){}
						Recover(sluiceID, left);
					}
				}
				pthread_cancel(threadID);
				pthread_detach(threadID);
				threadcheck = 0;
				return;
			}
    	}
    	Start(sluiceID);
  	}
}

void Administration::FreeEntry(int sluiceID)
{
	pthread_t   threadID;

	if(pthread_create(&threadID, NULL, myThread, &alarmCheck) != 0)
	{
		std::cout << "Error cant create thread" << std::endl;
	}
	
	Sluice* sluice = GetSluiceFromList(sluiceID);
	if(sluice->GetWaterLevel() == low)
	{
		Door* d = sluice->GetLeftDoor();
		if(sluice->GetLeftDoor()->GetState() == doorClosed || sluice->GetLeftDoor()->GetState() == doorLocked)
		{
			sluice->GetLeftDoor()->OpenDoor();
			while(sluice->GetLeftDoor()->GetState() != doorOpen)
			{
				if(alarmCheck == 1)
					{
						Alarm(sluiceID, left);
						while(alarmCheck == 1){}
						Recover(sluiceID, left);
					}
				}
			d->TurnLightRed(d->GetExit());
			d->TurnLightGreen(d->GetEntry());
			
		}
		else{
			d->TurnLightRed(d->GetExit());
			d->TurnLightGreen(d->GetEntry());
			
		}
	}
	else if(sluice->GetWaterLevel() == high)
	{
		Door* d = sluice->GetRightDoor();
		if(d->GetState() != doorOpen)
		{
			std::cout << "Error: door isn't open" << std::endl;
		}
		else{
			d->TurnLightRed(d->GetExit());
			d->TurnLightGreen(d->GetEntry());
			
		}
	}
	pthread_cancel(threadID);
	pthread_detach(threadID);
}

void Administration::FreeExit(int sluiceID)
{
	Sluice* sluice = GetSluiceFromList(sluiceID);
	if(sluice->GetWaterLevel() == low)
	{
		Door* d = sluice->GetLeftDoor();
		if(d->GetState() != doorOpen)
		{
			std::cout << "Error: door isn't open" << std::endl;
		}
		else{
			d->TurnLightRed(d->GetEntry());
			d->TurnLightGreen(d->GetExit());
			
		}
	}
	else if(sluice->GetWaterLevel() == high)
	{
		Door* d = sluice->GetRightDoor();
		if(d->GetState() != doorOpen)
		{
			std::cout << "Error: door isn't open" << std::endl;
		}
		else{
			d->TurnLightRed(d->GetEntry());
			d->TurnLightGreen(d->GetExit());
			
		}
	}
}

void Administration::Alarm(int sluiceID, DoorSide side)
{
	Sluice* sluice = GetSluiceFromList(sluiceID);
	if(side == left)
	{
		sluice->GetLeftDoor()->Stop();
		sluice->GetLeftDoor()->CloseAllValves();
	}
	else if(side == right)
	{
		sluice->GetRightDoor()->Stop();
		sluice->GetRightDoor()->CloseAllValves();
	}
	
}

void Administration::Recover(int sluiceID, DoorSide side)
{
	Sluice* sluice = GetSluiceFromList(sluiceID);
	if(side == left)
	{
		sluice->GetLeftDoor()->OpenDoor();
	}
	else if(side == right)
	{
		sluice->GetRightDoor()->OpenDoor();
	}
}

bool Administration::Add(Sluice* s)
{
    this->sluiceList.push_back(s);
    return true;
}

std::vector<Sluice*> Administration::GetSluiceList()
{
	return this->sluiceList;
}

Sluice* Administration::GetSluiceFromList(int ID)
{
	for(unsigned int i = 0; i < sluiceList.size();i++)
	{
		if(sluiceList[i]->GetSluiceID() == ID)
		{
			return sluiceList[i];
		}
	}
	return NULL;
}
