/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for MySocket.h
*/

#include "MySocket.h"

MilestoneTwo::MySocket::MySocket(SocketType newSocketType, std::string newIPAddr, int newPort, ConnectionType newConnectionType, int bufferLength)
{
	WelcomeSocket = INVALID_SOCKET;
	ConnectionSocket = INVALID_SOCKET;

	// Utilize member functions to set class variables
	SetType(newSocketType);				// Sets either Client or Server
	SetConnType(newConnectionType);		// Sets either TCP or UDP
	SetPortNo(newPort);
	SetIPAddr(newIPAddr);

	/* Is the passed in Buffer size less than zero (aka a negative)? If so, resort
		to using the DEFAULT_SIZE of 128 bytes, otherwise use the parameter */
	(bufferLength < 0 ? MaxSize = DEFAULT_SIZE : MaxSize = bufferLength);

	Buffer = new char[MaxSize];

	memset(Buffer, 0, MaxSize);

	// Start the Winsock library for our Socket
	start_DLLS();

	if (connectionType == TCP && mySocket == SERVER)
	{
		ConnectTCP();
	}
	else if (connectionType == UDP)
	{
		 // DO NOT initialize WelcomeSocket - that is used for TCP connections only!
		ConnectionSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
		if (ConnectionSocket == INVALID_SOCKET)
		{
			WSACleanup();
			std::cerr << "Could not initialize - INVALID_SOCKET" << std::endl; 
			std::cin.get();
			exit(0);
		}

		SvrAddr.sin_family = AF_INET;
		SvrAddr.sin_port = htons(this->Port);
		SvrAddr.sin_addr.s_addr = inet_addr(this->IPAddr.c_str());

		if (mySocket == SERVER)
		{
			if ((bind(this->ConnectionSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR)
			{
				closesocket(this->ConnectionSocket);
				WSACleanup();
				std::cerr << "Error while attempting to bind the Server socket" << std::endl;
				std::cin.get();
				exit(0);
			}
		}
	}
}

MilestoneTwo::MySocket::~MySocket()
{
	delete[] Buffer;
	Buffer = nullptr;
}

void MilestoneTwo::MySocket::start_DLLS()
{
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		std::cerr << "Could not start DLLs" << std::endl;
		exit(0);
	}
}

void MilestoneTwo::MySocket::ConnectTCP()
{
	// Initialize a Connection socket regardless of Client/Server/TCP or UDP (we ALWAYS need to do it!)
	ConnectionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectionSocket == INVALID_SOCKET)
	{
		WSACleanup();
		std::cerr << "Could not initialize - INVALID_SOCKET" << std::endl; //let people know of the connection error-hao
		std::cin.get();
		exit(0);
	}

	if (connectionType == TCP)
	{
		if (mySocket == CLIENT)
		{
			std::cout << "Trying to connect to the server" << std::endl;

			bTCPConnect = false;
			SvrAddr.sin_family = AF_INET;
			SvrAddr.sin_port = htons(this->Port);
			SvrAddr.sin_addr.s_addr = inet_addr(this->IPAddr.c_str());

			while (!bTCPConnect) {
				if ((connect(this->ConnectionSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
				}
				else {
					std::cout << "Connection Established" << std::endl;
					bTCPConnect = true;
				}
			}
		}
		else if (mySocket == SERVER)
		{
			WelcomeSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

			if (WelcomeSocket == INVALID_SOCKET)
			{
				WSACleanup();
				std::cerr << "Could not initialize WelcomeSocket" << std::endl;
				std::cin.get();
				exit(0);
			}

			SvrAddr.sin_family = AF_INET;
			SvrAddr.sin_port = htons(this->Port);
			SvrAddr.sin_addr.s_addr = inet_addr(this->IPAddr.c_str());

			if ((bind(this->WelcomeSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR)
			{
				closesocket(this->WelcomeSocket);
				WSACleanup();
				std::cerr << "Could bind the server's WelcomeSocket" << std::endl;
				std::cin.get();
				exit(0);
			}

			if (listen(this->WelcomeSocket, 1) == SOCKET_ERROR)
			{
				closesocket(this->WelcomeSocket);
				WSACleanup();
				std::cerr << "Could not listen to the provided socket" << std::endl;
				std::cin.get();
				exit(0);
			}
			else
			{
				std::cout << "Waiting for client connection..." << std::endl;
			}
			
			// NOTE: We must set the ConnectionSocket equal to the ServerSocket
			if ((this->ConnectionSocket = accept(this->WelcomeSocket, NULL, NULL)) == SOCKET_ERROR)
			{
				closesocket(this->WelcomeSocket);
				WSACleanup();
				std::cerr << "Could not accept incoming connection" << std::endl;
				std::cin.get();
				exit(0);
			}
			else
			{
				std::cout << "Connection Accepted" << std::endl;
				bTCPConnect = true;
			}
		}
	}
	else
	{
		std::cerr << "Connection type is not TCP! Cannot begin TCP connection!" << std::endl;
	}
}

void MilestoneTwo::MySocket::DisconnectTCP()
{
	if (mySocket == SERVER) { closesocket(WelcomeSocket); }
	
	closesocket(ConnectionSocket);
	
	// Free Winsock DLL resources
	WSACleanup();
}

void MilestoneTwo::MySocket::SendData(const char* rawData, int bufferLength)
{
	if (connectionType == TCP)
	{
		send(ConnectionSocket, rawData, bufferLength, 0);
	}
	else if (connectionType == UDP)
	{
		// ASSUMPTION: SvrAddr has been set properly beforehand
		sendto(ConnectionSocket, rawData, bufferLength, 0, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr));
	}
}

//Receive the last block of RAW data stored in the internal MySocket Buffer
int MilestoneTwo::MySocket::GetData(char* rawData)
{
	int numOfBytesReceived = 0;
	memset(Buffer, 0, MaxSize);

	// Check for TCP/UDP connection type before receiving
	if (connectionType == TCP) {
		numOfBytesReceived = recv(ConnectionSocket, Buffer, MaxSize, 0);

		memcpy(rawData, Buffer, numOfBytesReceived);
	}
	else if (connectionType == UDP) {
		int addrLen = sizeof(SvrAddr);
		numOfBytesReceived = recvfrom(ConnectionSocket, Buffer, MaxSize, 0, (struct sockaddr *)&SvrAddr, &addrLen);
		
		memcpy(rawData, Buffer, numOfBytesReceived);
	}
	else {
		std::cerr << "Invalid connection type, cannot receive incoming data!" << std::endl;
	}

	return numOfBytesReceived;
}

std::string MilestoneTwo::MySocket::GetIPAddr()
{
	return IPAddr;
}

void MilestoneTwo::MySocket::SetIPAddr(std::string newIPAddress)
{
	// Only allow modification of our IP Address if there is NOT a connection already established
	if (bTCPConnect || (GetType() == SERVER && WelcomeSocket != INVALID_SOCKET))
	{
		std::cerr << "Cannot change IP address, connection already established!" << std::endl;
	}
	else
	{
		IPAddr = newIPAddress;
	}
}

void MilestoneTwo::MySocket::SetPortNo(int newPortNumber)
{
	if (bTCPConnect || (GetType() == SERVER && WelcomeSocket != INVALID_SOCKET))
	{
		std::cerr << "Cannot change port number, connection already established!" << std::endl;
	}
	else
	{
		Port = newPortNumber;
	}
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
	if (bTCPConnect || (GetType() == SERVER && WelcomeSocket != INVALID_SOCKET))
	{
		std::cerr << "Cannot change socket type, connection already established!" << std::endl;
	}
	else
	{
		mySocket = newSocketType;
	}
}

void MilestoneTwo::MySocket::SetConnType(ConnectionType newConnType)
{
	if (bTCPConnect || (GetType() == SERVER && WelcomeSocket != INVALID_SOCKET))
	{
		std::cerr << "Cannot change connection type, connection already established!" << std::endl;
	}
	else
	{
		connectionType = newConnType;
	}
}

ConnectionType MilestoneTwo::MySocket::GetConnType()
{
	return connectionType;
}

void MilestoneTwo::MySocket::getWSAError()
{
	std::cout << WSAGetLastError();
}