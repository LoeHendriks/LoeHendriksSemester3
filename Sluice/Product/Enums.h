#ifndef ENUMS_H
#define ENUMS_H

enum ValveStatus
{
	open,
	closed
};

enum Control
{
	on,
	off
};

enum TrafficState
{
	red,
	green
};

enum WaterLevel
{
	low, 
	belowValve2,
	aboveValve2,
	aboveValve3,
	high
};

enum LockState
{
	lockWorking,
	lockDamaged
};

enum DoorState
{
	doorClosed,
	doorLocked,
	doorOpen,
	doorClosing,
	doorOpening,
	doorStopped,
	motorDamage
};

enum DoorSide
{
	left,
	right
};



#endif
