/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing all enumerations used for the entire project
*/

#ifndef PROJECT_PKTDEF_GLOBALS_H
#define PROJECT_PKTDEF_GLOBALS_H

/* Global list of typedef aliases found below */
typedef	unsigned int ui;
typedef unsigned char uc;

namespace MilestoneOne {
	enum CmdType				// Enumeration to define the command types for the Robot
	{
		DRIVE = 0,
		SLEEP,
		ARM,
		CLAW,
		ACK,
		STATUS
	};

	// Const integers to define all of the possible commands for the MotorBody structure

	// DRIVE command parameter definitions
	const ui FORWARD = 1;
	const ui BACKWARD = 2;
	const ui LEFT = 3;
	const ui RIGHT = 4;

	// ARM command parameter definitions
	const ui UP = 5;
	const ui DOWN = 6;

	// CLAW command parameter definitions
	const ui OPEN = 7;
	const ui CLOSE = 8;
	
	// Represents the size of the CmdPacketHeader structure in Bytes	
	const ui HEADERSIZE = 6;
	const ui HEADERSIZEOFFSET = 2;		// To account for the extra bytes added after the CmdPacket.Header structure
}
#endif