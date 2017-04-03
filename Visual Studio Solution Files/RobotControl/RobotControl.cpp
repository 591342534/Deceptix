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
					// Display RAW data packet
					std::cout << "RAW Data: " << RxBuffer << std::endl;

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

					// TODO: Setw() and format the output nicely

					// Display the Sonar reading followed by the Arm reading
					std::cout << "Sonar Reading of: " << body.SensorData << std::endl;

					std::cout << "Arm Reading of: " << body.ArmPositionData << std::endl;

					std::cout << "Drive flag is: " << body.Drive << std::endl;

					(body.ArmUp) ? std::cout << "Arm is Up," : std::cout << "Arm is Down,";

					(body.ClawOpen) ? std::cout << "Claw is Open" << std::endl : std::cout << "Claw is Closed" << std::endl;
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
	PktDef CommandPacket;
	char* RxBuffer = nullptr;
	char* TxBuffer = nullptr;
	bool sleepCondition = false;

	MySocket CommandSocket(SocketType::CLIENT, IPAddr, Port, ConnectionType::TCP, 100);
	CommandSocket.ConnectTCP();			// Perform the 3-way handshake to connect to a TCP server

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

		// Increment the PktCount number AFTER we generate the packet to send!
		CommandPacket.SetPktCount(CommandPacket.GetPktCount() + 1);

		CommandSocket.SendData(TxBuffer, CommandPacket.GetLength());

		// Wait for Senpai to acknowledge us
		int size = CommandSocket.GetData(RxBuffer);

		PktDef RobotPacket(RxBuffer);

		/* We need to check if the Megatron acknowledged the original command we sent! */
		if ((RobotPacket.GetCmd() == CommandPacket.GetCmd()) && RobotPacket.GetAck())
		{
			if (RobotPacket.CheckCRC(RxBuffer, size))	// Validating the Robots CRC
			{
				// Check if the SLEEP command we sent was RETURNED AND ACKNOWLEDGED by Megatron
				if ((CommandPacket.GetCmd() == SLEEP && RobotPacket.GetCmd() == SLEEP) && RobotPacket.GetAck())
				{

					ExeComplete = true;

					CommandSocket.DisconnectTCP();	// Disconnect the CommandSocket

													// Break from the Megatron's grasp
					break;
				}
				else		// Megatron acknowledged our request, let's display what he did
				{
					std::cout << "Megatron responded with an ACK of: " << RobotPacket.GetAck() << " for our " << RobotPacket.GetCmd() << " command" << std::endl;

					// Note: Need to add string mapping to enumeration for display purposes
				}
			}
			else
			{
				// We received an incorrect CRC from the Megatron! SABOTAGE!!!
				std::cout << "Incorrect CRC sent by Megatron. Dropping packet!" << RxBuffer;
			}
		}
		else if (RobotPacket.CheckNACK())	// We received a NACK from the Megatron, aka my dating life
		{
			std::cout << "Megatron responded with a NACK!" << std::endl;
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

	// First argument is the function we want to call (aka the logic), arguments thereafter are the ARGUMENTS to that specific function
	std::thread(CommandThreadLogic, argv[2], (int)argv[3]).detach();

	// Telemetry thread will use the same IP address as the command thread. 
	std::thread(TelemetryThreadLogic, argv[2], (int)argv[4]).detach();
		
	// Loop forever until ExeComplete is true!
	while (!ExeComplete) { }
}