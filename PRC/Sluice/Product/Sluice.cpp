#include "Sluice.h"
#include <string>
#include <iostream>


Sluice::Sluice(int sluiceID, WaterLevel heightWater, Connection* c)
{
    this->connection = c;
    this->sluiceID = sluiceID;
    this->heightWater = heightWater;

    if(sluiceID == 5557)
      {
        DoorSide ds = left;
        DoorSide ds2 = right;
        FastDoor* left = new FastDoor(ds, c);
        FastDoor* right = new FastDoor(ds2, c);
        this->leftDoor = left;
        this->rightDoor = right;

      }
      else if(sluiceID == 5558)
      {
        DoorSide ds = left;
        DoorSide ds2 = right;
        RestartDoor* left = new RestartDoor(ds, c);
        RestartDoor* right = new RestartDoor(ds2, c);
        this->leftDoor = left;
        this->rightDoor = right;
      }
      else if(sluiceID == 5555)
      {
        DoorSide ds = left;
        DoorSide ds2 = right;
        Door* left = new Door(ds, c);
        Door* right = new Door(ds2, c);
        this->leftDoor = left;
        this->rightDoor = right;
      }
      else if(sluiceID == 5556)
      {
        DoorSide ds = left;
        DoorSide ds2 = right;
        Door* left = new Door(ds, c);
        Door* right = new Door(ds2, c);
        this->leftDoor = left;
        this->rightDoor = right;
      }
}

Sluice::~Sluice()
{
    delete this->leftDoor;
    this->leftDoor = NULL;
    delete this->rightDoor;
    this->rightDoor = NULL;
}

int Sluice::GetSluiceID()
{
    return this->sluiceID;
}

void Sluice::SetSluiceID(int sluiceID)
{
    this->sluiceID = sluiceID;
}
       
Door* Sluice::GetLeftDoor()
{
    return leftDoor;
}
            

            
Door* Sluice::GetRightDoor()
{
    return rightDoor;
}
            


  
WaterLevel Sluice::GetWaterLevel()
{
    std::string tempstring = this->connection->Command("GetWaterLevel;");
    if(tempstring == "low;")
    {
        return low;
    }
    else if(tempstring == "belowValve2;")
    {
        return belowValve2;
    }
    else if(tempstring == "aboveValve2;")
    {
        return aboveValve2;
    }
    else if(tempstring == "aboveValve3;")
    {
        return aboveValve3;
    }
    else
    {
        return high;
    }
    
    

}
