/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for PktDef.h
*/

#include "PktDef.h"

PktDef::PktDef()
{
	/*
		Constructor inside each structure handles initialization to 0.
		See CmdPacket.h and CmdPacketHeader.h
	*/
	CmdPacket.Header.Length = HEADERSIZE + sizeof(uc);
	RawBuffer = nullptr;
}

PktDef::PktDef(char* rawData)		// Constructor called when we receive a stream of raw data
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
		CmdPacket.Header.Sleep || CmdPacket.Header.Ack)
	{
		/*
			If none of the flag bits were set, we received a NACK (Negative Acknowledgement) response
				OR
			If the SLEEP or ACK flag bit is set to 1, CmdPacket.Body's length will be 0 so don't bother allocating it.
			Simply calculate the CRC and we're all finished
		*/
		delete CmdPacket.Data;
		CmdPacket.Data = nullptr;
		CmdPacket.Header.Length = HEADERSIZE + sizeof(uc);
	}
	else if (CmdPacket.Header.Drive || CmdPacket.Header.Claw || CmdPacket.Header.Arm)
	{
		/*
			If the DRIVE, CLAW or ARM flag bits are set, this means that we will have data inside CmdPacket.Data.
			Specifically, this will be in the form of a MotorBody structure so we'll need to parse the information
			into one as required.
		*/

		// Move the pointer by 8 bytes to the beginning of the section inside rawData that contains the MotorBody values
		ptr += (HEADERSIZE + HEADERSIZEOFFSET);

		MotorBody mb;

		memcpy(&mb.Direction, ptr, sizeof(uc));

		ptr += sizeof(uc);

		memcpy(&mb.Duration, ptr, sizeof(uc));

		SetBodyData(reinterpret_cast<char*>(&mb), sizeof(MotorBody));
	}
	else if (CmdPacket.Header.Status)
	{
		/*
			If the STATUS bit is set, it means that we're receiving telemetry data from the robot. This could refer to
			values from the sonar sensors, the battery voltage or something else.
		*/

		ptr += HEADERSIZE;	// Do NOT need HEADERSIZEOFFSET since our rawData is contiguous inside rawData!

		/*
			The parsed Length of the entire packet minus the HEADERSIZE will give us the remaining amount of bytes to
			copy for the dynamic body content.
		*/
		SetBodyData(ptr, CalculateBodyLength());
	}

	// Calculate the CRC and store it inside CmdPacket.Tail
	CalcCRC();

	/*
		We need to call GenPacket() to make sure that all of our data is sequential.
		We MAY have a body, CmdPacket.Data, and if we try to pass in CmdPacket, our data will
		not be sequential. Therefore, generate the packet which will copy everything sequentially
		inside RawBuffer.
	*/
	GenPacket();

	// Verify if the calculated CRC is valid, if not then call the default constructor
	if (!CheckCRC(RawBuffer, CmdPacket.Header.Length))
	{
		PktDef();
	}

	// Because we're good students :)
	ptr = nullptr;
}

void PktDef::SetCmd(CmdType newCmdType)
{
	switch (newCmdType)
	{
	case DRIVE:
		CmdPacket.Header.Drive = 1;
		CmdPacket.Header.Sleep = 0;
		CmdPacket.Header.Arm = 0;
		CmdPacket.Header.Claw = 0;
		CmdPacket.Header.Ack = 0;
		break;
	case SLEEP:
		CmdPacket.Header.Drive = 0;
		CmdPacket.Header.Sleep = 1;
		CmdPacket.Header.Arm = 0;
		CmdPacket.Header.Claw = 0;
		CmdPacket.Header.Ack = 0;

		delete CmdPacket.Data;
		CmdPacket.Data = nullptr;

		CmdPacket.Header.Length = HEADERSIZE + sizeof(uc);
		break;
	case ARM:
		CmdPacket.Header.Drive = 0;
		CmdPacket.Header.Sleep = 0;
		CmdPacket.Header.Arm = 1;
		CmdPacket.Header.Claw = 0;
		CmdPacket.Header.Ack = 0;
		break;
	case CLAW:
		CmdPacket.Header.Drive = 0;
		CmdPacket.Header.Sleep = 0;
		CmdPacket.Header.Arm = 0;
		CmdPacket.Header.Claw = 1;
		CmdPacket.Header.Ack = 0;
		break;
	case ACK:
		CmdPacket.Header.Ack = 1;
	default:
		break;
	}
}

void PktDef::SetBodyData(char* rawData, int bufferLength)
{
	// Initialize the specified amount of bytes required
	CmdPacket.Data = new char[bufferLength];

	// Initialize the newly allocated memory to 0 using the size bufferLength
	memset(CmdPacket.Data, 0, bufferLength);

	/*
		Copy the provided data into the body of CmdPacket

		NOTE: Do NOT copy into the memory location of the pointer
		itself but the location to which the pointer POINTS TO.
		ex: DO NOT DO => memcpy(&CmdPacket.Data, ..., ...);
	*/
	memcpy(CmdPacket.Data, rawData, bufferLength);

	CmdPacket.Header.Length = HEADERSIZE + bufferLength + sizeof(CmdPacket.CRC);
}

void PktDef::SetPktCount(int newPktCount)
{
	CmdPacket.Header.PktCount = newPktCount;
}

CmdType PktDef::GetCmd()
{
	// Return the CmdType based on the set flag bit
	if (CmdPacket.Header.Drive) { return DRIVE; }
	else if (CmdPacket.Header.Sleep) { return SLEEP; }
	else if (CmdPacket.Header.Arm) { return ARM; }
	else if (CmdPacket.Header.Claw) { return CLAW; }
	else if (CmdPacket.Header.Ack) { return ACK; }
	else if (CmdPacket.Header.Status) { return STATUS; }
	else { return NACK; }
}

bool PktDef::GetAck()
{
	/*
		Is the Header's ACK flag set equal to 1? (aka is it true?),
		if so, return TRUE otherwise return FALSE.
	*/
	return (CmdPacket.Header.Ack == 1 ? true : false);
}

int PktDef::GetLength()
{
	return CmdPacket.Header.Length;
}

int PktDef::CalculateBodyLength()		// Additional function to calculate the dynamic body's size
{
	return (CmdPacket.Header.Length - HEADERSIZE - sizeof(uc));
}

char* PktDef::GetBodyData()
{
	return (CmdPacket.Data == nullptr ? nullptr : CmdPacket.Data);
}

int PktDef::GetPktCount()
{
	return CmdPacket.Header.PktCount;
}

bool PktDef::CheckCRC(char* rawData, int bufferLength)
{
	// Assumption: CRC value for the current CmdPacket is initialized
	char* ptr = rawData;
	int counter = 0;

	// Loop through rawData one byte at a time
	for (int i = 0; i < (bufferLength - 1); i++)
	{
		// Check one bit at a time
		for (int j = 0; j < 8; j++)
		{
			if (((*ptr >> j) & 0x01) == 0x01)
			{
				counter++;
			}
		}

		// Move to the next byte
		ptr++;
	}

	return (counter == *ptr);
}

void PktDef::CalcCRC()
{
	// Kindly ask ze pointer to point to the beginning of CmdPacket's header
	char* ptr = (char*)&CmdPacket.Header;

	int counter = 0;

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

		// Move to the next byte
		ptr++;
	}

	// Done counting the number of 1's inside the Header so let's set it to nullptr to be safe
	ptr = nullptr;

	/*
		Next, let's count the number of bits set to 1 inside the body: CmdPacket.Data.
		==> We must keep in mind that the Body is dynamic memory so we have to calculate
			the amount of bytes that the Body will take. We created a helper function,
			CalculateBodyLength() which will do the dirty work for us.

		We MUST NOT forget to set the pointer to the beginning of this data - you will be reading
		something else and counting irrelevant 1's!
	*/

	// If we don't point to anything, skip the following logic
	if (GetBodyData() != nullptr)
	{
		// Kindly ask ze pointer to point to the CmdPacket's body (remember it's dynamic memory so no &)
		ptr = CmdPacket.Data;

		// Loop through CmdPacket.Body one byte at a time
		for (int sean = 0; sean < CalculateBodyLength(); sean++)
		{
			for (int nathaniel = 0; nathaniel < 8; nathaniel++)
			{
				if (((*ptr >> nathaniel) & 0x01) == 0x01)
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

char* PktDef::GenPacket()
{
	// Allocate memory for data transfer
	RawBuffer = new char[GetLength()];

	// Helper pointer for traversing dynamic data of the packet
	char* ptr = RawBuffer;

	// Copying packet header
	memcpy(ptr, &CmdPacket.Header, HEADERSIZE);
	ptr += (HEADERSIZE);

	if ((GetCmd() == DRIVE) || (GetCmd() == CLAW) || (GetCmd() == ARM))
	{
		// Copying packet body
		memcpy(ptr, CmdPacket.Data, CalculateBodyLength());

		ptr += CalculateBodyLength();
	}

	// Copying packet tail
	memcpy(ptr, &CmdPacket.CRC, sizeof(uc));

	// BONUS MARKS!
	ptr = nullptr;

	// Return the RawBuffer
	return RawBuffer;
}

PktDef::~PktDef()
{
	// Need to use delete[] if the "new" keyword is used!
	delete[] RawBuffer;
	RawBuffer = nullptr;
}