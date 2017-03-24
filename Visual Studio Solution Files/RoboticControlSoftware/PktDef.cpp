/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for PktDef.h
*/

#include "PktDef.h"

MilestoneOne::PktDef::PktDef()
{
	/* Constructor inside each structure handles initialization to 0.
		See CmdPacket.h and CmdPacketHeader.h */
	RawBuffer = nullptr;
}

MilestoneOne::PktDef::PktDef(char* rawData)
{
	char* ptr = rawData;

	// Extract and populate CmdPacket.Header
	memcpy(&CmdPacket.Header, ptr, HEADERSIZE);

	/* Move the pointer past CmdPacket.Header to now
		point to the beginning of the Body */
	ptr += HEADERSIZE;

	// Dynamically allocate the body using the previously copied CmdPacket.Header.Length
	CmdPacket.Body = new char[CmdPacket.Header.Length];

	// Extract and populate the dynamic contents of CmdPacket.Body
	memcpy(CmdPacket.Body, ptr, CmdPacket.Header.Length);

	/* Move the pointer past CmdPacket.Body to now
		point to the beginning of the Tail */
	ptr += CmdPacket.Header.Length;

	// Extract and populate CmdPacket.Tail (aka the CRC value)
	memcpy(&CmdPacket.Tail, ptr, sizeof(uc));

	ptr = nullptr;
}

void MilestoneOne::PktDef::SetCmd(CmdType newCmdType)
{
	switch (newCmdType)
	{
	case DRIVE:
		CmdPacket.Header.Drive = 1;
		break;
	case SLEEP:
		CmdPacket.Header.Sleep = 1;
		break;
	case ARM:
		CmdPacket.Header.Arm = 1;
		break;
	case CLAW:
		CmdPacket.Header.Claw = 1;
		break;
	case ACK:
		CmdPacket.Header.Ack = 1;
		// No break necessary unless default has varying logic
	default:
		break;
	}
}

void MilestoneOne::PktDef::SetBodyData(char* rawData, int bufferLength)
{
	// Initialize the specified amount of bytes required
	CmdPacket.Body = new char[bufferLength];

	// Initialize the newly allocated memory to 0 using the size bufferLength
	memset(CmdPacket.Body, 0, bufferLength);

	// Copy the provided data into the body of CmdPacket
	/* NOTE: Do NOT copy into the memory location of the pointer
		itself but the location to which the pointer POINTS TO.
		ex: DO NOT DO => memcpy(&CmdPacket.Body, ..., ...);
	*/
	memcpy(CmdPacket.Body, rawData, bufferLength);
}

void MilestoneOne::PktDef::SetPktCount(int newPktCount)
{
	CmdPacket.Header.PktCount = newPktCount;
}

MilestoneOne::CmdType MilestoneOne::PktDef::GetCmd()
{
	// Return the CmdType based on the set flag bit
	if (CmdPacket.Header.Drive == 1) { return DRIVE; }
	else if (CmdPacket.Header.Sleep == 1) { return SLEEP; }
	else if (CmdPacket.Header.Arm == 1) { return ARM; }
	else if (CmdPacket.Header.Claw == 1) { return CLAW; }
	else if (CmdPacket.Header.Ack == 1) { return ACK; }
}

bool MilestoneOne::PktDef::GetAck()
{
	/* Is the Header's ACK flag set equal to 1? (aka is it true?),
		if so, return TRUE otherwise return FALSE */
	return (CmdPacket.Header.Ack == 1 ? true : false);
}

int MilestoneOne::PktDef::GetLength()
{
	return 0;
}

char* MilestoneOne::PktDef::GetBodyData()
{
	return nullptr;
}

int MilestoneOne::PktDef::GetPktCount()
{
	return 0;
}

bool MilestoneOne::PktDef::CheckCRC(char*, int)
{
	return true;
}

void MilestoneOne::PktDef::CalcCRC()
{

}

char* MilestoneOne::PktDef::GenPacket()
{
	return nullptr;
}

MilestoneOne::PktDef::~PktDef()
{
	delete RawBuffer;
	RawBuffer = nullptr;
}