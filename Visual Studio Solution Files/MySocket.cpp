/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for MySocket.h
*/

#include "MySocket.h"

MilestoneTwo::MySocket::MySocket()
{
	Buffer = nullptr;
}

MilestoneTwo::MySocket::MySocket(SocketType newSocketType, std::string newIPAddr, int newPort, ConnectionType newConnectionType, int bufferLength)
{
	// Have fun Stephen
	Buffer = nullptr;
}

MilestoneTwo::MySocket::~MySocket()
{
	delete Buffer;
	Buffer = nullptr;
}

// Start the Windows DLL (Dynamic Linked Library) for Winsock
void MilestoneTwo::MySocket::start_DLLS()
{
	//if ((WSAStartup(MAKEWORD(this->version_num1, this->version_num2), &this->wsa_data)) != 0) {
	//	std::cout << "Could not start DLLs" << std::endl;
	//	exit(0);
	//}

	// Have fun Stephen
}

void MilestoneTwo::MySocket::ConnectTCP()
{
	// 3 way handshakes (but I only gots 2 hands)

	// Have fun Stephen
}

void MilestoneTwo::MySocket::DisconnectTCP()
{
	// 4 way handshake (use your legs too)

	// Have fun Stephen
}

void MilestoneTwo::MySocket::SendData(const char* rawData, int bufferLength)
{
	if (connectionType == TCP)
	{
		//send() for TCP connections
	}
	else if (connectionType == UDP)
	{
		//sendto() for UDP connections
	}

	// Have fun Hao
}

int MilestoneTwo::MySocket::GetData(char* rawData)
{
	return 0;
}

std::string MilestoneTwo::MySocket::GetIPAddr()
{
	return IPAddr;
}

void MilestoneTwo::MySocket::SetIPAddr(std::string newIPAddress)
{
	if (bTCPConnect)
	{
		// Whatchu tryin to do changing my IP all up in here?
	}
	else
	{
		// Aye aye cap'n. Change my IP anyway you want
	}

	// Have fun Hao
}

void MilestoneTwo::MySocket::SetPortNo(int newPortNumber)
{
	Port = newPortNumber;
}

int MilestoneTwo::MySocket::GetPort()
{
	return Port;
}

SocketType MilestoneTwo::MySocket::GetType()
{
	return mySocket;
}

void MilestoneTwo::MySocket::SetType(SocketType newSocketType)
{
	mySocket = newSocketType;

	/* What happens if we change from client to server? Do we need to reset/configure
		anything? Think carefully regarding our SvrAddr_in structure! */

	// Have fun Hao
}