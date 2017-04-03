/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for RobotControl.h
*/

#include "../MySocket.h"
#include "../ApplicationLayer/PktDef.h"

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

	/*while (!ExeComplete)
	{

	}*/
	
	MilestoneTwo::MySocket CommandSocket(SocketType::CLIENT, (std::string)argv[2], (int)argv[3], ConnectionType::TCP, 100);
	CommandSocket.ConnectTCP();			// Perform the 3-way handshake to connect to a TCP server
	MilestoneOne::PktDef CommandPacket;

	// Get all of the necessary data from the user

	// Generate the CRC before sending out packet
	CommandPacket.CalcCRC();
	char* RxBuffer = nullptr;
	char* TxBuffer = CommandPacket.GenPacket();

	// Increment the PktCount number
	CommandPacket.SetPktCount(CommandPacket.GetPktCount() + 1);

	CommandSocket.SendData(TxBuffer, CommandPacket.GetLength());

	CommandSocket.GetData(RxBuffer);

	// Print the results of what the robot said to us!
	std::cout << RxBuffer;
}