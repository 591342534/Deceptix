/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for CmdPacket.h
*/

#ifndef PROJECT_CMDPACKET_H
#define PROJECT_CMDPACKET_H

#include "CmdPacketHeader.h"
#include "CmdPacketBody.h"
#include "Enumerations.h"

namespace MilestoneOne {
	struct CmdPacket
	{
	private:
	public:
		CmdPacketHeader Header;
		//CmdPacketBody MotorBody;
		char* Data;
		char CRC;

		CmdPacket()
		{
			Data = nullptr;
			CRC = '\0';
		}
	};
}
#endif