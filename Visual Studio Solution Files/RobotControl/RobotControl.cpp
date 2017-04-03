/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for RobotControl.h
*/

#include "MySocket.h"
#include "PktDef.h"

void TelemetryThreadLogic(std::string IPAddr, int Port)
{
	MySocket TelemetrySocket(SocketType::CLIENT, IPAddr, Port, ConnectionType::TCP, 100);
	TelemetrySocket.ConnectTCP();	// Perform the 3-way handshake to connect to a TCP server
	PktDef TelemetryPacket;

	//ASSUMPTION: Packet body is structured in a specific sequence for parsing.
	char* RxBuffer = nullptr;
	//Receive and process incoming telemetry packets from the Robot continuously
	while (1) {
		//Reset the pointer 
		delete [] RxBuffer;
		RxBuffer = nullptr;
		//Receive incoming Telemetry Packet
		int bytesReceived = TelemetrySocket.GetData(RxBuffer);
		if (TelemetryPacket.CheckCRC(RxBuffer, bytesReceived)) {
			PktDef incomingTelPacket(RxBuffer);		//TODO: do we generate packet inside constructor? (GENPACKET function in constructor)
			int dataSize = incomingTelPacket.CalculateBodyLength();
			char* buffer = new char[dataSize];
			buffer = incomingTelPacket.GetBodyData();



		}




	}
}

void CommandThreadLogic(std::string IPAddr, int Port)
{
	MySocket CommandSocket(SocketType::CLIENT, IPAddr, Port, ConnectionType::TCP, 100);
	CommandSocket.ConnectTCP();			// Perform the 3-way handshake to connect to a TCP server
	PktDef CommandPacket;
	char* RxBuffer = nullptr;
	char* TxBuffer = nullptr;
	bool sleepCondition = false;

	// Set the PktCount number to 0 initially then each subsequent time we'll need to increment it
	CommandPacket.SetPktCount(0);
	
	while (1)
	{
		// TODO: Get all of the necessary data from the user
		//std::cout << "Please enter the details of the packet." << std::endl;
		//std::cout << "Format is as follows:" << std::endl << std::endl;
		//std::cout << "CommandType: " << std::endl << std::endl;
		
		// Generate the CRC before sending out packet
		CommandPacket.CalcCRC();

		TxBuffer = CommandPacket.GenPacket();

		// Increment the PktCount number
		CommandPacket.SetPktCount(CommandPacket.GetPktCount() + 1);

		CommandSocket.SendData(TxBuffer, CommandPacket.GetLength());

		// Get the response from the Robot
		int size = CommandSocket.GetData(RxBuffer);

		if (CommandPacket.CheckCRC(RxBuffer, size))	// Validating the Robots CRC
		{
			// Proceed to check if the SLEEP command was acknowledged
			char* ptr = RxBuffer;

			// Move past PktCount to the beginning of the bit fields
			ptr += sizeof(int);

			/*
				XX@X X@XX = 24 in HEX, AKA 0X24!
				Drive Status Sleep Arm || Claw Ack Pad Pad - 1 byte in total
			*/

			/*
				Check the positions that the SLEEP and ACK flags are positioned at,
				if they are BOTH set (bitwise AND will check) then we KNOW that a SLEEP
				flag AND an ACK flag has been sent by the Robot. We'll need to break from the loop!
			*/
			if (((*ptr) & 0X24) == 0X24 ? true : false)
			{
				CommandSocket.DisconnectTCP();	// Disconnect the MySocket

				ExeComplete = true;

				// Break from the infinity loop
				break;
			}
		}
		else 
		{
			// We received an incorrect CRC from the Robot! SABOTAGE!
			std::cout << "Incorrect CRC sent by Robot. Dropping packet!" << RxBuffer;
		}
	}
}

int main(int argc, char *argv[])
{
	std::cout << "Command Line : ";

	for (int i = 1; i < argc; i++)
	{
		std::cout << argv[i] << " ";
	}

	if ((argc < 3) || (argv == NULL))	/* .Exe file path always submitted via argv, therefore
										recognize more than 1 argument which indicates some type of user input */
	{
		std::cout << "Insufficient number of arguments (minimum of 2)" << std::endl;

		exit(0);
	}

	ExeComplete = false;

	// Spawn both the Command Telemetry thread then detach from the main process
	// NOTE PASS SHTIT TO CMD THREAD

	// First argument is the function we want to call (aka the logic), arguments thereafter are the ARGUMENTS to that specific function
	std::thread(CommandThreadLogic, argv[2], (int)argv[3]);

	//Telemetry thread will use the same IP address as the command thread. 
	std::thread(TelemetryThreadLogic, argv[2], (int)argv[4]);

	
	// Loop forever until ExeComplete is true!
	while (!ExeComplete) { }
}