/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing a MotorBody structure
*/

#ifndef PROJECT_TELEMETRYBODY_H
#define PROJECT_TELEMETRYBODY_H

#include "MySocket.h"
#include "PktDef.h"

struct TelemetryBody
{
private:
public:
	us SensorData;			// Holds the Sonar Sensor Data (2 bytes #worth)
	us ArmPositionData;		// Holds a value that specifies the duration of a command (in seconds)
	uc Drive : 1;
	uc ArmUp : 1;
	uc ArmDown : 1;
	uc ClawOpen : 1;
	uc ClawClosed : 1;
	uc Padding : 2;

	TelemetryBody()
	{
		SensorData = 0;
		ArmPositionData = 0;
		Drive = 0;
		ArmUp = 0;
		ArmDown = 0;
		ClawOpen = 0;
		ClawClosed = 0;
		Padding = 0;
	}
};
#endif