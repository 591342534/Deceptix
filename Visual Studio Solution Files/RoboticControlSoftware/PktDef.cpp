/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for PktDef.h
*/

#include "PktDef.h"

/* Sean completed the seven functions listed below - March 24, 2017 */

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
	else { return ERROR; }
}

bool MilestoneOne::PktDef::GetAck()
{
	/* Is the Header's ACK flag set equal to 1? (aka is it true?),
		if so, return TRUE otherwise return FALSE */
	return (CmdPacket.Header.Ack == 1 ? true : false);
}

/* Hao completed the six functions listed below - March 24, 2017 */

int MilestoneOne::PktDef::GetLength()
{
	/* Assumption: CmdPacket.Body is allocated to a max of 2 bytes (for the struct MotorBody)
		6 + 1 - 4 + 2 = Expected value of 5 bytes
		CmdPacket.Header + Tail - 1 Pointer (char* Body) + MotorBody (which is a max of 2 bytes)
	*/
	return sizeof(CmdPacket) + (sizeof(char)*CmdPacket.Header.Length) - 4;
}

char* MilestoneOne::PktDef::GetBodyData()
{
	return CmdPacket.Body;
}

int MilestoneOne::PktDef::GetPktCount()
{
	return CmdPacket.Header.PktCount;
}

bool MilestoneOne::PktDef::CheckCRC(char* rawData, int bufferLength)
{
	// Assumption: CRC value for the current CmdPacket is initialized

	int counter = 0;

	// TODO 1 - Find a new home for sizeOfNotTail
	// Christened by Hao Chen - March 24, 2017
	const ui sizeOfNotTail = HEADERSIZE + (sizeof(char) * CmdPacket.Header.Length);

	// Loop through rawData one byte at a time
	for (ui i = 0; i < sizeOfNotTail; i++) {
		// Check one bit at a time
		for (int j = 0; j < 8; j++) {
			if (((rawData[i] >> j) & 0x01) == 0x01) {
				counter++;
			}
		}
	}

	return (counter == CmdPacket.Tail);
}

void MilestoneOne::PktDef::CalcCRC()
{
	int counter = 0;

	// TODO 2 - Find a new home for sizeOfNotTail
	// Christened by Hao Chen - March 24, 2017
	const ui sizeOfNotTail = HEADERSIZE + (sizeof(char) * CmdPacket.Header.Length);

	// Loop through rawData one byte at a time
	for (ui i = 0; i < sizeOfNotTail; i++) {
		// Check one bit at a time
		for (int j = 0; j < 8; j++) {
			if (((RawBuffer[i] >> j) & 0x01) == 0x01) {
				counter++;
			}
		}
	}

	// Set CRC value
	CmdPacket.Tail = counter;
}

char* MilestoneOne::PktDef::GenPacket()
{
	// Calculate how much memory allocation is required for RawBuffer
	// GetLength() returns the length of: Header + Body + Tail
	int size = GetLength();

	// Allocate memory for data transfer
	RawBuffer = new char[size];

	// Helper pointer for traversing dynamic data of the packet
	char* ptr = RawBuffer;

	// Copying packet header
	memcpy(ptr, &CmdPacket.Header, HEADERSIZE);
	ptr += HEADERSIZE;

	// Copying packet body
	memcpy(ptr, CmdPacket.Body, (sizeof(char)*CmdPacket.Header.Length));
	ptr += sizeof(char)*CmdPacket.Header.Length;

	// Copying packet tail
	memcpy(ptr, &CmdPacket.Tail, sizeof(uc));

	// TODO: BONUS MARKS
	ptr = nullptr;

	// Return the RawBuffer
	return RawBuffer;
}

MilestoneOne::PktDef::~PktDef()
{
	delete RawBuffer;
	RawBuffer = nullptr;
}