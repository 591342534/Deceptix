/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing all enumerations used for the entire project
*/

#ifndef PROJECT_PKTDEF_ENUMERATIONS_H
#define PROJECT_PKTDEF_ENUMERATIONS_H

/* Global list of typdef aliases found below */
typedef	unsigned int ui;
typedef unsigned char uc;

namespace MilestoneOne {
	enum CmdType				/* Enumeration to define the command types for the Robot */
	{
		DRIVE,
		SLEEP,
		ARM,
		CLAW,
		ACK
	};

	enum Cmd					/* Enumeration to define all of the possible commands
								for the MotorBody structure */
	{
		FORWARD = 1,
		BACK,
		RIGHT,
		LEFT,
		UP,
		DOWN,
		OPEN,
		CLOSE
	};

	const ui HEADERSIZE = 6;	// Represents the size of the CmdPacketHeader structure in Bytes (counted manually)
}
#endif