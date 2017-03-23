/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	Implementation file for PktDef.h
*/

#include "PktDef.h"

MilestoneOne::PktDef::PktDef()
{
	
}

MilestoneOne::PktDef::PktDef(char* newData)
{
	
}

void MilestoneOne::PktDef::SetCmd(CmdType newCmdType)
{

}

void MilestoneOne::PktDef::SetBodyData(char*, int)
{

}

void MilestoneOne::PktDef::SetPktCount(int)
{

}

MilestoneOne::CmdType MilestoneOne::PktDef::GetCmd()
{
	return CmdType::SLEEP;
}

bool MilestoneOne::PktDef::GetAck()
{
	return true;
}

int MilestoneOne::PktDef::GetLength()
{
	return 0;
}

char* MilestoneOne::PktDef::GetBodyData()
{
	return nullptr;
}

int MilestoneOne::PktDef::GetPktCount()
{
	return 0;
}

bool MilestoneOne::PktDef::CheckCRC(char*, int)
{
	return true;
}

void MilestoneOne::PktDef::CalcCRC()
{

}

char* MilestoneOne::PktDef::GenPacket()
{
	return nullptr;
}