/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing the MySocket class
*/

#ifndef PROJECT_MYSOCKET_H
#define PROJECT_MYSOCKET_H

#include "ApplicationLayer/Globals.h"
#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")

namespace MilestoneTwo {
	class MySocket {
	private:
		char* Buffer;						// RAW buffer space for communication activities
		SOCKET WelcomeSocket;				// Used by a MySocket object configured as a TCP/IP SERVER
		SOCKET ConnectionSocket;			// Used for client/server communications (Both TCP and UDP)
		struct sockaddr_in SvrAddr;			// Stores connection information
		SocketType mySocket;				// Holds the type of socket that the MySocket object is initialized to
		std::string IPAddr;					// Holds the IPV4 IP Address string
		int Port;							// Holds the port number to be used
		ConnectionType connectionType;		// Defines the Transport layer protocol being used (Either TCP or UDP)
		bool bTCPConnect;					// Determines if a connection has been established or not
		int MaxSize;						/* Stores the maximum number of bytes the buffer is allocated to -
												helps prevent overflows and synchronization issues */
		void getWSAError();					/* Used for debugging purposes:
											https://msdn.microsoft.com/en-us/library/windows/desktop/ms740668(v=vs.85).aspx */
	public:
		MySocket(SocketType, std::string, int, ConnectionType, int);
		~MySocket();
		void start_DLLS();
		void ConnectTCP();
		void DisconnectTCP();
		void SendData(const char*, int);
		void SetIPAddr(std::string);
		void SetPortNo(int);
		void SetType(SocketType);
		void SetConnType(ConnectionType);
		int GetData(char*);
		std::string GetIPAddr();
		int GetPort();
		SocketType GetType();
		ConnectionType GetConnType();
	};
}
#endif