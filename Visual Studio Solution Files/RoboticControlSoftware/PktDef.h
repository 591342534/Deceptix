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

#include <string.h>
#include "Globals.h"
#include "CmdPacket.h"

namespace MilestoneOne {
	class PktDef {
	private:
		CmdPacket CmdPacket;			// Contains Header, Data and CRC
		MotorBody MotorBody;			// Contains drive parameter information
		char* RawBuffer;				// Stores all data in PktDef in a serialized form that is used for transmission over TCP/IP
	public:
		PktDef();						// Default constructor that initializes to a safe state
		PktDef(char*);					// Takes a RAW data buffer, parses and populates the Header, Body and CRC
		void SetCmd(CmdType);			// Sets the packets command flag based on the CmdType argument
		void SetBodyData(char*, int);	/* Takes a ptr to a RAW data buffer and allocates packets Body field then
											copies the provided data into the objects buffer */
		void SetPktCount(int);			// Sets the objects PktCount header variable
		CmdType GetCmd();				// Returns the CmdType based on the set command flag bit
		bool GetAck();					// Returns a boolean value based on the ACK flag in the Header
		int GetLength();				// Returns the length of the packet in bytes
		char* GetBodyData();			// Returns a ptr to the objects Body field
		int GetPktCount();				// Returns the PktCount value
		bool CheckCRC(char*, int);		/* Takes a ptr to a RAW data buffer, the size of the buffer in bytes and calculates the CRC.
											If the CRC matches the CRC of the packet in the buffer, return TRUE otherwise FALSE */
		void CalcCRC();					// Calculates the CRC and sets the objects packet CRC parameter
		char* GenPacket();				/* Allocates the private RawBuffer member variable and transfers the contents from the objects member variables
											into a RAW data packet (RawBuffer) for transmission. The address of the allocated RawBuffer is returned. */
		~PktDef();						// Destructor for dynamic memory
	};
}
#endif