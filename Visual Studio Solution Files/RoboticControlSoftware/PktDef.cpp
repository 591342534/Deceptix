/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for PktDef.h
*/

#include "PktDef.h"

/* Sean completed the first seven functions listed below - March 24, 2017 */

MilestoneOne::PktDef::PktDef()
{
	/* Constructor inside each structure handles initialization to 0.
		See CmdPacket.h and CmdPacketHeader.h */
	CmdPacket.Header.Length = HEADERSIZE + sizeof(uc);
	RawBuffer = nullptr;
}

MilestoneOne::PktDef::PktDef(char* rawData)	// Constructor called when we receive a stream of raw data
{
	char* ptr = rawData;

	// Extract and populate CmdPacket.Header
	memcpy(&CmdPacket.Header, ptr, HEADERSIZE);

	/*
		Next, we need to check the type of packet that we just received based on the flag bits
		set inside the freshly parsed CmdPacket.Header. Refer to MilestoneOne Instructions for
		the various types of packets that we can receive.
	*/

	if ((!CmdPacket.Header.Drive && !CmdPacket.Header.Status && !CmdPacket.Header.Sleep
		&& !CmdPacket.Header.Ack && !CmdPacket.Header.Claw && !CmdPacket.Header.Ack) ||
		(CmdPacket.Header.Sleep || CmdPacket.Header.Ack))
	{
		/*	If none of the flag bits were set, we received a NACK (Negative Acknowledgement) response
				OR
			If the SLEEP or ACK flag bit is set to 1, CmdPacket.Body's length will be 0 so don't bother allocating it.
			Simply calculate the CRC and we're all finished
		*/
		//CmdPacket.Header.Length = HEADERSIZE + sizeof(CmdPacket.CRC);
		CmdPacket.Data = nullptr;
	}
	else if (CmdPacket.Header.Drive || CmdPacket.Header.Claw || CmdPacket.Header.Arm)
	{
		/* If the DRIVE, CLAW or ARM flag bits are set, this means that we will have data inside CmdPacket.Data.
			Specifically, this will be in the form of a MotorBody structure so we'll need to parse the information
			into one as required. */

		// Move the pointer by 8 bytes to the beginning of the section inside rawData that contains the MotorBody values
		ptr += HEADERSIZE + HEADERSIZEOFFSET;

		memcpy(&MotorBody, ptr, sizeof(MilestoneOne::MotorBody));

		CmdPacket.Header.Length = HEADERSIZE + sizeof(MilestoneOne::MotorBody) + sizeof(uc);

		// Set the CmdPacket.Data pointer to point to the MotorBody structure that has just been populated
		CmdPacket.Data = (char*)&MotorBody;
	}
	else if (CmdPacket.Header.Status)
	{
		/* If the STATUS bit is set, it means that we're receiving telemetry data from the robot. This could refer to
			values from the sonar sensors, the battery voltage or something else */

		/* Size of the buffer that we're receiving minus CmdPacket.Header will give us the remaining number
			of bytes to copy. This allows us to have a dynamic */

		ptr += HEADERSIZE;	// Do NOT need HEADERSIZEOFFSET since our rawData is sequential!

		int lengthOfBodyDataToCopy = CmdPacket.Header.Length - HEADERSIZE;

		SetBodyData(ptr, lengthOfBodyDataToCopy);
	}

	CalcCRC();
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
	CmdPacket.Data = new char[bufferLength];

	// Initialize the newly allocated memory to 0 using the size bufferLength
	memset(CmdPacket.Data, 0, bufferLength);

	// Copy the provided data into the body of CmdPacket
	/* NOTE: Do NOT copy into the memory location of the pointer
		itself but the location to which the pointer POINTS TO.
		ex: DO NOT DO => memcpy(&CmdPacket.Body, ..., ...);
	*/
	memcpy(CmdPacket.Data, rawData, bufferLength);

	CmdPacket.Header.Length = HEADERSIZE + bufferLength + sizeof(CmdPacket.CRC);
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
	else { return UNSPECIFIED; }
}

bool MilestoneOne::PktDef::GetAck()
{
	/* Is the Header's ACK flag set equal to 1? (aka is it true?),
		if so, return TRUE otherwise return FALSE */
	return (CmdPacket.Header.Ack == 1 ? true : false);
}

/* Hao completed the remaining six functions listed below - March 24, 2017 */

int MilestoneOne::PktDef::GetLength()
{
	return CmdPacket.Header.Length;
}

char* MilestoneOne::PktDef::GetBodyData()
{
	return CmdPacket.Data;
}

int MilestoneOne::PktDef::GetPktCount()
{
	return CmdPacket.Header.PktCount;
}

bool MilestoneOne::PktDef::CheckCRC(char* rawData, int bufferLength)
{
	// Assumption: CRC value for the current CmdPacket is initialized

	char* ptr = rawData;
	int counter = 0;

	// Loop through rawData one byte at a time
	for (int i = 0; i < bufferLength; i++)
	{
		// Check one bit at a time
		for (int j = 0; j < 8; j++)
		{
			if (((*ptr >> j) & 0x01) == 0x01)
			{
				counter++;
			}
		}
		ptr++;	// Move to the next byte
	}

	return (counter == CmdPacket.CRC);
}

void MilestoneOne::PktDef::CalcCRC()
{
	char* ptr = nullptr;
	int counter = 0;

	// Kindly ask ze pointer to point to the beginning of CmdPacket's header
	ptr = (char*)&CmdPacket.Header;

	// Loop through CmdPacket.Header one byte at a time
	for (int hao = 0; hao < HEADERSIZE; hao++)
	{
		// Check one bit at a time
		for (int stephen = 0; stephen < 8; stephen++)
		{
			if (((*ptr >> stephen) & 0X01) == 0X01)
			{
				counter++;
			}
		}
		ptr++;	// Move to the next byte
	}

	// Done counting the number of 1's inside the Header so let's set it to nullptr to be safe
	ptr = nullptr;

	/* Next, let's count the number of bits set to 1 inside the body, CmdPacket.Body.
		We must keep in mind that the Body is dynamic memory so we have to rely on the "Length"
		variable inside our header, CmdPacket.Header.Length, to give us the amount of bytes that
		has been allocated.

		We MUST NOT forget to set the pointer to the beginning of this data - you will be reading
		something else and counting irrelevant 1's
	*/

	// If we don't point to anything, skip the code below
	if (GetBodyData() != nullptr)
	{
		// Kindly ask ze pointer to point to the CmdPacket's body (remember it's dynamic memory)
		ptr = CmdPacket.Data;

		// Loop through CmdPacket.Body one byte at a time
		for (int sean = 0; sean < (GetLength() - HEADERSIZE - sizeof(CmdPacket.CRC)); sean++)
		{
			for (int maurice = 0; maurice < 8; maurice++)
			{
				if (((*ptr >> maurice) & 0x01) == 0x01)
				{
					counter++;
				}
			}
			ptr++;
		}

		// Done counting the number of 1's inside the Body so let's set it to nullptr to be safe
		ptr = nullptr;
	}

	// Set the CmdPacket's CRC value from all of the bits that we found were 1
	CmdPacket.CRC = counter;
}

char* MilestoneOne::PktDef::GenPacket()
{
	/* Calculate how much memory allocation is required for RawBuffer
		GetLength() returns the length of: Header + Body + Tail */
	int size = GetLength();

	// Allocate memory for data transfer
	RawBuffer = new char[size];

	// Helper pointer for traversing dynamic data of the packet
	char* ptr = RawBuffer;

	// Copying packet header
	memcpy(ptr, &CmdPacket.Header, HEADERSIZE + HEADERSIZEOFFSET);
	ptr += (HEADERSIZE + HEADERSIZEOFFSET);

	// Copying packet body
	memcpy(ptr, CmdPacket.Data, sizeof(CmdPacket.Data));
	ptr += sizeof(CmdPacket.Data);

	// Copying packet tail
	memcpy(ptr, &CmdPacket.CRC, sizeof(uc));

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