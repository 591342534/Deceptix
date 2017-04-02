/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for RobotControl.h
*/

#include "../MySocket.h"
#include "../ApplicationLayer/Globals.h"

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

	//MilestoneTwo::MySocket TCPClientSocket(SocketType::CLIENT, "127.0.0.1", 5000, ConnectionType::TCP, 100);

	MilestoneTwo::MySocket commandSocket(SocketType::CLIENT, std::string(argv[2]), (int)argv[3], ConnectionType::TCP, 100);

	std::thread threadOne(&MilestoneTwo::MySocket::ConnectTCP, &commandSocket);

	//std::thread threadTwo();
	//threadOne(threadTwo(), ).detach();
}