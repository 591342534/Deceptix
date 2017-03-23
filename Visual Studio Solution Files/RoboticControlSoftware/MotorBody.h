/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing a MotorBody structure that may be received inside the body of CmdPacket
*/

#ifndef PROJECT_MOTORBODY_H
#define PROJECT_MOTORBODY_H

namespace MilestoneOne {
	struct MotorBody
	{
	private:
	public:
		uc Direction;		// Holds a value that corresponds to one of the following commands: DRIVE, ARM, CLAW
		uc Duration;		// Holds a value that specifies the duration of a command (in seconds)

		MotorBody()
		{
			Direction = 0;
			Duration = 0;
		}
	};
}
#endif