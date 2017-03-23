/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing a CmdPacketBody structure for the CmdPacket struct
*/

#ifndef PROJECT_CMDPACKET_BODY_H
#define PROJECT_CMDPACKET_BODY_H

typedef unsigned char uc;

namespace MilestoneOne {
	struct CmdPacketBody
	{
	private:
	public:
		uc Direction;		// Holds a value that corresponds to one of the following commands: DRIVE, ARM, CLAW
		uc Duration;		// Holds a value that specifies the duration of a command (in seconds)

		CmdPacketBody()
		{
			Direction = 0;
			Duration = 0;
		}
	};
}
#endif