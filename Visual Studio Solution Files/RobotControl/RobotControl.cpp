/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for RobotControl.h
*/

#include "MySocket.h"
#include "PktDef.h"
#include "RobotControl.h"

void TelemetryThreadLogic(std::string IPAddr, int Port)
{
	MySocket TelemetrySocket(SocketType::CLIENT, IPAddr, Port, ConnectionType::TCP, 100);
	TelemetrySocket.ConnectTCP();	// Perform the 3-way handshake to connect to a TCP server
	
	// ASSUMPTION: Packet body is structured in a specific sequence for parsing.
	char* RxBuffer = nullptr;

	// Receive and process incoming Telemetry packets from the Robot forever
	while (1)
	{
		// Delete the contents of RxBuffer from the previous Telemetry packet
		delete [] RxBuffer;
		RxBuffer = nullptr;

		// Receive the incoming Telemetry data from the Robot
		int bytesReceived = TelemetrySocket.GetData(RxBuffer);

		PktDef TelemetryPacket(RxBuffer);

		try
		{
			// Calculate the CRC on our end and compare if the Robot's CRC is the same!
			if (TelemetryPacket.CheckCRC(RxBuffer, bytesReceived))
			{
				// If the calculated CRC is good, move onto verification of the Header (AKA STATUS BIT SET!
				if (TelemetryPacket.GetStatus())
				{
					// All checks have passed! Let's display the raw Telemetry data

					TelemetryBody body;

					// TODO: Upgrade from double to decimal for the Sonar Reading
					char* ptr = RxBuffer;
					
					ptr += sizeof(CmdPacketHeader);

					// Now we're at the beginning of the body (which is 5 bytes in length)
					memcpy(&body.SensorData, ptr, sizeof(unsigned short));

					ptr += sizeof(unsigned short);

					memcpy(&body.ArmPositionData, ptr, sizeof(unsigned short));

					ptr += sizeof(unsigned short);

					// We're now at the beginning of the bit fields so let's copy them in!
					body.Drive = ((*ptr) >> 0) & 0X01;
					body.ArmUp = ((*ptr) >> 1) & 0X01;
					body.ArmDown = ((*ptr) >> 2) & 0X01;
					body.ClawOpen = ((*ptr) >> 3) & 0X01;
					body.ClawClosed = ((*ptr) >> 4) & 0X01;
				}
				else { throw "Status bit was not set for Telemetry data. Dropping packet."; }
			}
			else { throw "An invalid CRC was detected. Dropping packet."; }
		}
		catch (const char* errorMessage)
		{
			std::cerr << errorMessage << std::endl;
		}
		catch (...)
		{
			std::cerr << "ERROR: An unknown error was caught!" << std::endl;
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