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
	Welcome	
}

MilestoneTwo::MySocket::MySocket(SocketType, std::string, ui, ConnectionType, ui)
{

}

MilestoneTwo::MySocket::~MySocket()
{

}

void MilestoneTwo::MySocket::ConnectTCP()
{

}

void MilestoneTwo::MySocket::DisconnectTCP()
{

}

void MilestoneTwo::MySocket::SendData(const char*, int)
{

}

int MilestoneTwo::MySocket::GetData(char*)
{
	return 0;
}

std::string MilestoneTwo::MySocket::GetIPAddr()
{
	return std::string();
}

void MilestoneTwo::MySocket::SetIPAddr(std::string)
{

}

void MilestoneTwo::MySocket::SetPort(int)
{

}

int MilestoneTwo::MySocket::GetPort()
{
	return 0;
}

SocketType MilestoneTwo::MySocket::GetType()
{
	return CLIENT;
}

void MilestoneTwo::MySocket::SetType(SocketType)
{

}