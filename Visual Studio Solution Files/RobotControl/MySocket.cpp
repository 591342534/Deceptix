/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for MySocket.h
*/

#include "MySocket.h"

/* Constructor that configures the socket and connection types as well as IP Address and Port number
	as well as dynamically allocating memory for the receiving buffer. Servers are setup accordingly. */
MySocket::MySocket(SocketType newSocketType, std::string newIPAddr, int newPort, ConnectionType newConnectionType, int bufferLength)
{
	// Start the Winsock library for our Socket
	start_DLLS();

	// Initialize both sockets
	WelcomeSocket = INVALID_SOCKET;
	ConnectionSocket = INVALID_SOCKET;

	SvrAddr.sin_family = AF_INET;		// Specifies to use IP
	SetType(newSocketType);				// Sets either Client or Server
	connectionType = newConnectionType;
	SetPortNo(newPort);
	SetIPAddr(newIPAddr);

	/* Is the passed in Buffer size less than zero (aka a negative)? If so, resort
		to using the DEFAULT_SIZE of 128 bytes, otherwise use the parameter */
	(bufferLength < 0 ? MaxSize = DEFAULT_SIZE : MaxSize = bufferLength);

	Buffer = new char[MaxSize];
	memset(Buffer, 0, MaxSize);

	bTCPConnect = false;

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

// Destructor to deallocate dynamic data
MySocket::~MySocket()
{
	delete[] Buffer;
	Buffer = nullptr;
}

// Boots up the Windows socket libraries (to use functions like send, recv etc)
void MySocket::start_DLLS()
{
	WSADATA wsaData;
	if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
		std::cerr << "Could not start DLLs" << std::endl;
		exit(0);
	}
}

// Function used to establish a TCP/IP socket connection via a 3-way handshake
void MySocket::ConnectTCP()
{
	if (connectionType == TCP)
	{
		ConnectionSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (ConnectionSocket == INVALID_SOCKET)
		{
			WSACleanup();
			std::cerr << "Could not initialize - INVALID_SOCKET" << std::endl;
			std::cin.get();
			exit(0);
		}

		SvrAddr.sin_family = AF_INET;
		SetPortNo(Port);
		SetIPAddr(IPAddr);
		bTCPConnect = false;

		if (mySocket == CLIENT)
		{
			std::cout << "Trying to connect to the server" << std::endl;

			while (!bTCPConnect) {
				if ((connect(this->ConnectionSocket, (struct sockaddr *)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR)
				{
					std::this_thread::sleep_for(std::chrono::milliseconds(200));
				}
				else {
					bTCPConnect = true;
					std::cout << "Connection Established" << std::endl;
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
				bTCPConnect = true;
				std::cout << "Connection Accepted" << std::endl;
			}
		}
	}
	else
	{
		std::cerr << "Connection type is not of TCP! Cannot perform a TCP connection!" << std::endl;
	}
}

// Function used to disconnect an established TCP/IP socket connection via a 4-way handshake
void MySocket::DisconnectTCP()
{
	if (bTCPConnect)
	{
		if (mySocket == SERVER) { closesocket(WelcomeSocket); }

		closesocket(ConnectionSocket);

		bTCPConnect = false;

		// Free Winsock DLL resources
		WSACleanup();
	}
}

// Function used to transmit a block of RAW data - works with both TCP and UDP
void MySocket::SendData(const char* rawData, int bufferLength)
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

// Function used to receive data on the internal buffer then copy it to the argument buffer. Works with both TCP and UDP
int MySocket::GetData(char* rawData)
{
	int numOfBytesReceived = 0;
	memset(Buffer, 0, MaxSize);

	// Check for TCP/UDP connection type before receiving
	if (connectionType == TCP) {
		numOfBytesReceived = recv(ConnectionSocket, Buffer, MaxSize, 0);

		memcpy(rawData, Buffer, numOfBytesReceived);
	}
	else if (connectionType == UDP) {
		int addr_len = sizeof(sockaddr);

		numOfBytesReceived = recvfrom(ConnectionSocket, Buffer, MaxSize, 0, (struct sockaddr *)&SvrAddr, &addr_len);

		memcpy(rawData, Buffer, numOfBytesReceived);
	}
	else {
		std::cerr << "Invalid connection type, cannot receive incoming data!" << std::endl;
	}

	return numOfBytesReceived;
}

// Sets an IP Address - contains logic to prevent changes being made if a TCP/IP connection has been established or Welcome socket is open
void MySocket::SetIPAddr(std::string newIPAddress)
{
	// Only allow modification of our IP Address if there is NOT a connection already established
	if (bTCPConnect || (GetType() == SERVER && WelcomeSocket != INVALID_SOCKET))
	{
		std::cerr << "Cannot change IP address, connection already established!" << std::endl;
	}
	else
	{
		IPAddr = newIPAddress;
		SvrAddr.sin_addr.s_addr = inet_addr(IPAddr.c_str());
	}
}

// Sets a Port number - contains logic to prevent changes being made if a TCP/IP connection has been established or Welcome socket is open
void MySocket::SetPortNo(int newPortNumber)
{
	if (bTCPConnect || (GetType() == SERVER && WelcomeSocket != INVALID_SOCKET))
	{
		std::cerr << "Cannot change port number, connection already established!" << std::endl;
	}
	else
	{
		Port = newPortNumber;
		SvrAddr.sin_port = htons(Port);
	}
}

// Sets a Socket Type - contains logic to prevent changes being made if a TCP/IP connection has been established or Welcome socket is open
void MySocket::SetType(SocketType newSocketType)
{
	if (bTCPConnect || (GetType() == SERVER && WelcomeSocket != INVALID_SOCKET))
	{
		std::cerr << "Cannot change socket type, connection already established!" << std::endl;
	}
	else
	{
		mySocket = newSocketType;

		// TODO: Implement logic for switching between a TCP client/server
	}
}

std::string MySocket::GetIPAddr()
{
	return IPAddr;
}

int MySocket::GetPort()
{
	return Port;
}

SocketType MySocket::GetType()
{
	return mySocket;
}

// Function used during debugging to display error codes from functions like send(), recv(), sendto() and recvfrom()
void MySocket::getWSAError()
{
	std::cout << "Last known error code of: " << WSAGetLastError() << std::endl;
}