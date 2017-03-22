/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file for PktDef.cpp
					~ The PktDef class contains the robots application layer protocol. This includes
					~ a header, body and tail.
*/

#ifndef PROJECT_PKTDEF_H
#define PROJECT_PKTDEF_H

#include "PktDefHeader.h"
#include "Enum.h"

namespace MilestoneOne {
	class PktDef {
	private:
		Header Header;
	public:
		PktDef()
		{
			
		}
	};
}
#endif