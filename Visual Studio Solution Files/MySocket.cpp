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
	mySocket = newSocketType;
	Port = newPort;
	IPAddr = newIPAddr;
	connectionType = newConnectionType;
	MaxSize = bufferLength;
	Buffer = nullptr;
	//Connect
	if (connectionType == TCP)
	{
		start_DLLS();
		ConnectTCP();
	}
}

MilestoneTwo::MySocket::~MySocket()
{
	delete Buffer;
	Buffer = nullptr;
}

// Start the Windows DLL (Dynamic Linked Library) for Winsock
void MilestoneTwo::MySocket::start_DLLS()
{
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		std::cout << "Could not start DLLs" << std::endl;
		exit(0);
	}
}

void MilestoneTwo::MySocket::ConnectTCP()
{
	//Initialize
	ConnectionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectionSocket == INVALID_SOCKET)
	{
		WSACleanup();
		exit(0);
	}
	// 3 way handshakes (but I only gots 2 hands)
	//3 way handshake for Connection Socket
	if (connectionType == TCP)
	{
		//Client
		if (mySocket == CLIENT)
		{
			std::cout << "Trying to connect to the server" << std::endl;

			bTCPConnect = false;
			SvrAddr.sin_family = AF_INET;
			SvrAddr.sin_port = htons(this->Port);
			SvrAddr.sin_addr.s_addr = inet_addr(this->IPAddr.c_str());
			while (!bTCPConnect)
			{
				if ((connect(this->ConnectionSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR)
				{
					closesocket(this->ConnectionSocket);
					WSACleanup();
					std::cout << "Could not connect to the server" << std::endl;
					std::cin.get();
					exit(0);
				}
				else {
					std::cout << "Connection Established" << std::endl;
					bTCPConnect = true;
				}
			}
		}//if CLIENT CONNECTION
		 //SERVER
		if (mySocket == SERVER)
		{
			SvrAddr.sin_family = AF_INET;
			SvrAddr.sin_port = htons(this->Port);
			SvrAddr.sin_addr.s_addr = inet_addr(this->IPAddr.c_str());
			//Bind
			if ((bind(this->ConnectionSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR)
			{
				closesocket(this->ConnectionSocket);
				WSACleanup();
				std::cout << "Could not connect to the server" << std::endl;
				std::cin.get();
				exit(0);
			}
			//listen
			if (listen(this->ConnectionSocket, 1) == SOCKET_ERROR)
			{
				closesocket(this->ConnectionSocket);
				WSACleanup();
				std::cout << "Could not listen to the provided socket." << std::endl;
				std::cin.get();
				exit(0);
			}
			else
			{
				std::cout << "Waiting for client connection..." << std::endl;
			}
			//Accept
			if ((this->ConnectionSocket = accept(this->ConnectionSocket, NULL, NULL)) == SOCKET_ERROR)
			{
				closesocket(this->ConnectionSocket);
				WSACleanup();
				std::cout << "Could not accept incoming connection." << std::endl;
				std::cin.get();
				exit(0);
			}
			else
			{
				std::cout << "Connection Accepted" << std::endl;
			}
		}//If SERVER

	}
}

void MilestoneTwo::MySocket::DisconnectTCP()
{
	//4 way handshake Connection Socket
	closesocket(ConnectionSocket); //closes connection and socket
	WSACleanup(); //frees Winsock DLL resources
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