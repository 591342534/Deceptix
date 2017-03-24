/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for CmdPacket.h
*/

#ifndef PROJECT_CMDPACKET_H
#define PROJECT_CMDPACKET_H

#include "CmdPacketHeader.h"
#include "MotorBody.h"

namespace MilestoneOne {
	struct CmdPacket
	{
	private:
	public:
		CmdPacketHeader Header;		// Note: Structure within a structure
		char* Body;					/* The data could be raw telemetry, empty or a MotorBody structure.
										It must be dynamic and generic, not specific to MotorBody - Elliot 2017 */
		uc Tail;					// Contains the CRC value

		CmdPacket()
		{
			Body = nullptr;
			Tail = 0;
		}
	};
}
#endif