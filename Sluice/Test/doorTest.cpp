#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../Product/Door.h"
//#include "../Product/Connection.h"

using ::testing::Return;
using ::testing::_;

class TestDoor : public ::testing::Test{
	protected:

	Door* door;
	Connection connection;
    TestDoor() {
       door = new Door(left, &connection);
		connection.Connect(5555);
    }

    virtual ~TestDoor() {
        delete door;
        door = NULL;
    }

};


TEST_F(TestDoor, test_TurnLightGreen_turns_Light_green)
{
	door->TurnLightGreen(door->GetEntry());
	EXPECT_EQ(on, door->GetEntry()->GetGreen());
	
}
TEST_F(TestDoor, test_TurnLightRed_turns_Light_Red)
{
	door->TurnLightRed(door->GetEntry());
	EXPECT_EQ(on, door->GetEntry()->GetRed());
	
}

TEST_F(TestDoor, test_GetSide_Returns_a_Side)
{
	EXPECT_EQ(left, door->GetSide());
	
}

TEST_F(TestDoor, test_SetState_sets_state)
{
	door->SetState(doorClosed);
	EXPECT_EQ(doorClosed, door->GetState());
}

TEST_F(TestDoor, test_GetState_uses_command)
{
	EXPECT_EQ(doorClosed, door->GetState());
	
}

TEST_F(TestDoor, test_OpenDoor_is_opening_after_calling_Opendoor)
{
	door->OpenDoor();
	EXPECT_EQ(doorOpening, door->GetState());
}

TEST_F(TestDoor, test_OpenDoor_state_is_open_after_opening)
{
	while(door->GetState() == doorOpening){}
	EXPECT_EQ(doorOpen, door->GetState());
}

TEST_F(TestDoor, test_CloseDoor_is_closing_after_calling_CloseDoor)
{
	while(door->GetState() != doorOpen){}
	door->CloseDoor();
	EXPECT_EQ(doorClosing, door->GetState());
}

TEST_F(TestDoor, test_CloseDoor_is_closed_after_closing)
{
	while(door->GetState() == doorClosing){}
	EXPECT_EQ(doorClosed, door->GetState());
}

TEST_F(TestDoor, test_OpenValve_opens_Valve)
{
	door->OpenValve(door->GetLowValve());
	EXPECT_EQ(open, door->GetLowValve()->GetStatus());
}

TEST_F(TestDoor, test_CloseValve_closes_Valve)
{
	door->CloseValve(door->GetLowValve());
	EXPECT_EQ(closed, door->GetLowValve()->GetStatus());
}

TEST_F(TestDoor, test_CloseAllValve_closes_all_Valve)
{
	door->OpenValve(door->GetLowValve());
	door->OpenValve(door->GetMediumValve());
	door->OpenValve(door->GetHighValve());
	door->CloseAllValves();
	EXPECT_EQ(closed, door->GetLowValve()->GetStatus());
	EXPECT_EQ(closed, door->GetMediumValve()->GetStatus());
	EXPECT_EQ(closed, door->GetHighValve()->GetStatus());
}


