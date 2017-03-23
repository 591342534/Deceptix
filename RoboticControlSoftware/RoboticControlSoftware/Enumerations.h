/*
Title:			BTN415 Project - Robotic Control Software - Winter 2016
Author(s):		Sean Prashad, Hao Chen, Stephen Noble
Student ID:		029-736-105, 022-905-152, 018-619-155
Description:	~ Header file containing all enumerations used for the entire project
*/

#ifndef PROJECT_PKTDEF_ENUMERATIONS_H
#define PROJECT_PKTDEF_ENUMERATIONS_H

namespace MilestoneOne {
	enum CmdType			/* Enumeration to define the command types */
	{
		DRIVE,
		SLEEP,
		ARM,
		CLAW,
		ACK
	};

	enum DRIVE				/* Enumeration containing pre-defined values associated with driving directions */
	{
		FORWARD = 1,		// Start at the index of 1, instead of 0
		BACK,
		RIGHT,
		LEFT
	};

	enum ARM				/* Enumeration containing pre-defined values associated with vertical arm movement */
	{
		UP = 5,				// Start at the index of 5, instead of 0
		DOWN
	};

	enum CLAW				/* Enumeration containing pre-defined values associated with arm instructions*/
	{
		OPEN = 7,			// Start at the index of 7, instead of 0
		CLOSE
	};
}
#endif