/*
	Title:			BTN415 Project - Robotic Control Software - Winter 2016
	Author(s):		Sean Prashad, Hao Chen, Stephen Noble
	Student ID:		029-736-105, 022-905-152, 018-619-155
	Description:	~ Header file containing items used for the entire project
*/

#ifndef PROJECT_PKTDEF_GLOBALS_H
#define PROJECT_PKTDEF_GLOBALS_H

/* Global list of typedef aliases found below */
typedef	unsigned int ui;
typedef unsigned short us;
typedef unsigned char uc;

#include <iostream>
#include <string>
#include <thread>
#include <map>

/* Default namespace */
enum SocketType
{
	CLIENT = 0,
	SERVER
};

enum ConnectionType
{
	TCP = 0,
	UDP
};

const ui DEFAULT_SIZE = 128;			// Max size of our Buffer for the MySocket class
static bool ExeComplete = false;		// Global flag used for Robot control execution

enum CmdType				// Enumeration to define the command types for the Robot
{
	DRIVE = 0,
	SLEEP,
	ARM,
	CLAW,
	ACK,
	STATUS = 200,
	NACK = 404
};

// DRIVE command parameter definitions
const ui FORWARD = 1;
const ui BACKWARD = 2;
const ui RIGHT = 3;
const ui LEFT = 4;

// ARM command parameter definitions
const ui UP = 5;
const ui DOWN = 6;

// CLAW command parameter definitions
const ui OPEN = 7;
const ui CLOSE = 8;

// Represents the size of the CmdPacketHeader structure in Bytes	
const ui HEADERSIZE = 6;
const ui HEADERSIZEOFFSET = 2;		// To account for the extra bytes added after the CmdPacket.Header structure

// A map for retrieving CmdType value
static std::map<CmdType, std::string> mapOfCmdTypes = {
	{ CmdType::DRIVE, "DRIVE" },
	{ CmdType::SLEEP, "SLEEP" },
	{ CmdType::ARM, "ARM" },
	{ CmdType::CLAW, "CLAW" },
	{ CmdType::ACK , "ACK"},
	{ CmdType::STATUS , "STATUS"},
	{ CmdType::NACK , "NACK"}
};

// Return the correct CmdType for command
static std::string cmdTypeEquivalent(CmdType commandType) {
	return mapOfCmdTypes[commandType];
}

// Function to display an integer value to it's respective time counterpart
void static ConvertToMinutes(int value, int &minute, int &seconds)
{
	minute = (value % 3600) / 60;
	seconds = value % 60;
}
#endif