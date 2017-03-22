/*
Title:			BTN415 Project - Robotic Control Software - Winter 2016
Author(s):		Sean Prashad, Hao Chen, Stephen Noble
Student ID:		029-736-105, 022-905-152, 018-619-155
Description:	~ Header file containing a Body structure for the PktDef class
*/

#ifndef PROJECT_PKTDEF_BODY_H
#define PROJECT_PKTDEF_BODY_H

typedef unsigned char uc;

namespace MilestoneOne {
	struct Body
	{
	private:
	public:
		uc Direction;		// Holds a value that corresponds to one of the following commands: DRIVE, ARM, CLAW
		uc Duration;		// Holds a value that specifies the duration of a command (in seconds)

		Body()
		{
			Direction = 0;
			Duration = 0;
		}
	};
}
#endif