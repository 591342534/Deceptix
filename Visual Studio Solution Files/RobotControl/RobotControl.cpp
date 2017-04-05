/*
Title:			BTN415 Project - Robotic Control Software - Winter 2016
Author(s):		Sean Prashad, Hao Chen, Stephen Noble
Student ID:		029-736-105, 022-905-152, 018-619-155
Description:	Implementation file for RobotControl.h
*/

#include "RobotControl.h"

void TelemetryThreadLogic(std::string IPAddr, int Port)
{
	MySocket TelemetrySocket(SocketType::CLIENT, IPAddr, Port, ConnectionType::TCP, 100);
	TelemetrySocket.ConnectTCP();	// Perform the 3-way handshake to connect to a TCP server

									// ASSUMPTION: Packet body is structured in a specific sequence for parsing
	char* RxBuffer = new char[DEFAULT_SIZE];

	// Receive and process incoming Telemetry packets from the Megatron forever
	while (1)
	{
		// Delete the contents of RxBuffer from the previous Telemetry packet
		memset(RxBuffer, 0, DEFAULT_SIZE);

		// Receive the incoming Telemetry data from the Megatron
		int bytesReceived = TelemetrySocket.GetData(RxBuffer);

		// Create a packet based on the data received from Megatron
		PktDef TelemetryPacket(RxBuffer);

		try
		{
			// Calculate the CRC on our end and compare if the Megatron's CRC is the same!
			if (TelemetryPacket.CheckCRC(RxBuffer, bytesReceived))
			{
				// If the calculated CRC is good, move onto verification of the Header (AKA STATUS BIT SET!
				if (TelemetryPacket.GetStatus())
				{
					std::cout << std::endl << std::endl << "RECEIVED TELEMETRY PACKET:" << std::endl;

					std::cout << "RAW Data Bytes: ";

					for (int i = 0; i < bytesReceived; i++)
					{
						std::cout << std::hex << (int)RxBuffer[i] << ", ";
					}

					// Reset the output back to standard values
					std::cout << std::dec << std::endl;

					// All checks have passed! Let's display the raw Telemetry data
					TelemetryBody body;

					char* ptr = RxBuffer + sizeof(int) + (sizeof(char) * 2);

					/* Now we're at the beginning of the body (which is 5 bytes in length),
					let's copy the first section - Sonar Sensor data */
					memcpy(&body.SensorData, ptr, sizeof(us));

					// Move onto the Arm Position data
					ptr += sizeof(us);

					// Copy in the the Arm Position data
					memcpy(&body.ArmPositionData, ptr, sizeof(us));

					// Move past the Arm Position data and onto the bit fields
					ptr += sizeof(us);

					// We're now at the beginning of the bit fields so let's copy them in!
					body.Drive = ((*ptr) >> 0) & 0X01;
					body.ArmUp = ((*ptr) >> 1) & 0X01;
					body.ArmDown = ((*ptr) >> 2) & 0X01;
					body.ClawOpen = ((*ptr) >> 3) & 0X01;
					body.ClawClosed = ((*ptr) >> 4) & 0X01;

					// Display the Sonar reading followed by the Arm reading
					std::cout << "Sonar Value = " << body.SensorData << ",  ";

					std::cout << "Arm Position = " << body.ArmPositionData << std::endl;

					std::cout << "Drive flag is: " << (ui)body.Drive << std::endl;

					(body.ArmUp) ? std::cout << "Arm is Up" << std::endl : std::cout << "Arm is Down" << std::endl;

					(body.ClawOpen) ? std::cout << "Claw is Open" << std::endl : std::cout << "Claw is Closed" << std::endl;
				}
				else { throw "Status bit was not set for Telemetry data. Dropping packet."; }
			}
			else { throw "An invalid CRC was detected. Dropping packet."; }
		}
		catch (const char* errorMessage)
		{
			std::cerr << errorMessage << std::endl;
		}
		catch (...)
		{
			std::cerr << "ERROR: An unknown error was caught!" << std::endl;
		}
	}
}

void CommandThreadLogic(std::string IPAddr, int Port)
{
	PktDef CommandPacket;
	char* RxBuffer = nullptr;
	char* TxBuffer = nullptr;
	int minutes = 0, seconds = 0;

	MySocket CommandSocket(SocketType::CLIENT, IPAddr, Port, ConnectionType::TCP, 100);
	CommandSocket.ConnectTCP();			// Perform the 3-way handshake to connect to a TCP server

										// Set the PktCount number to 0 initially then each subsequent time we'll need to increment it
	CommandPacket.SetPktCount(0);

	while (1)
	{
		/*
		Consider commands the user can enter:

		Drive - requires drive bit to be set in header AND
		a body consisting of a MOTORBODY struct!

		Arm - requires arm bit to be set in header AND
		a body consisting of a MOTORBODY struct!

		Claw - requires claw bit to be set in header AND
		a body consisting of a MOTORBODY struct!
		*/

		std::cout << "Select a command to tell Megatron to do:" << std::endl << std::endl;
		std::cout << "0 - DRIVE\n1 - SLEEP\n2 - ARM\n3 - CLAW" << std::endl;

		// Get the user's choice then act upon it - convert it to an integer
		int commandType = -1;		/* http://stackoverflow.com/questions/13421965/using-cin-get-to-get-an-integer */
		std::cin >> commandType;

		if ((commandType == 0) || (commandType == 1) || (commandType == 2) || (commandType == 3))
		{
			CmdType commandTypeEnum;

			switch (commandType)
			{
			case 0:
				commandTypeEnum = DRIVE;
				break;
			case 1:
				commandTypeEnum = SLEEP;
				break;
			case 2:
				commandTypeEnum = ARM;
				break;
			case 3:
				commandTypeEnum = CLAW;
				break;
			}

			CommandPacket.SetCmd(commandTypeEnum);

			if (commandTypeEnum == SLEEP)
			{
				CommandPacket.SetBodyData(nullptr, 0);	// Clear the body since it's a SLEEP command
			}
			else
			{
				// User wants to enter a DRIVE, ARM or CLAW command! Get a MotorBody struct ready!

				MotorBody motorBody;
				int direction = 0, duration = 0;

				switch (commandTypeEnum)
				{
				case 0:
					std::cout << "Choose from the following directions:" << std::endl;
					std::cout << "1 - FORWARD\n2 - BACKWARD\n3 - RIGHT\n4 - LEFT" << std::endl;

					std::cin >> direction;

					switch (direction)
					{
					case FORWARD:
						motorBody.Direction = FORWARD;
						break;
					case BACKWARD:
						motorBody.Direction = BACKWARD;
						break;
					case RIGHT:
						motorBody.Direction = RIGHT;
						break;
					case LEFT:
						motorBody.Direction = LEFT;
						break;
					default:
						break;
					}

					std::cout << "Enter the duration for the DRIVE command: ";
					std::cin >> duration;

					motorBody.Duration = (uc)duration;
					break;
				case 2:
					std::cout << "Choose from the following directions:" << std::endl;
					std::cout << "5 - UP\n6 - DOWN" << std::endl;

					std::cin >> direction;

					switch (direction)
					{
					case UP:
						motorBody.Direction = UP;
						break;
					case DOWN:
						motorBody.Direction = DOWN;
						break;
					default:
						break;
					}

					motorBody.Duration = 0;
					break;
				case 3:

					std::cout << "Choose from the following directions:" << std::endl;
					std::cout << "7 - OPEN\n8 - CLOSE" << std::endl;

					std::cin >> direction;

					switch (direction)
					{
					case OPEN:
						motorBody.Direction = OPEN;
						break;
					case CLOSE:
						motorBody.Direction = CLOSE;
						break;
					default:
						break;
					}

					motorBody.Duration = 0;
					break;
				}

				CommandPacket.SetBodyData(reinterpret_cast<char*>(&motorBody), sizeof(MotorBody));

				// Call the user-define time formatting function
				ConvertToMinutes(motorBody.Duration, minutes, seconds);
			}
		}
		else
		{
			std::cout << "SOMETHING WENT WRONG!" << std::endl;
		}

				/*
				Generate the CRC before sending out packet!

				NOTE: Body is stored as unsigned char, aka the ASCII equivalent
				to what our user entered. If the user entered "1" and "2" for the Motorbody,
				it stores the ASCII equivalent which is'31' and '32'. This results in the
				number of 1's being different than what we expected.
				*/
				CommandPacket.CalcCRC();

				TxBuffer = CommandPacket.GenPacket();

				// Increment the PktCount number AFTER we generate the packet to send!
				CommandPacket.SetPktCount(CommandPacket.GetPktCount() + 1);

				CommandSocket.SendData(TxBuffer, CommandPacket.GetLength());

				// Clean up any existing data inside the Buffer
				delete[] RxBuffer;
				RxBuffer = new char[CommandPacket.GetLength()];

				// Wait for Senpai to acknowledge us
				int size = CommandSocket.GetData(RxBuffer);

				PktDef RobotPacket(RxBuffer);

				/* We need to check if the Megatron acknowledged the original command we sent! */
				if ((RobotPacket.GetCmd() == CommandPacket.GetCmd()) && RobotPacket.GetAck())
				{
					if (RobotPacket.CheckCRC(RxBuffer, size))	// Validating the Robots CRC
					{
						// Check if the SLEEP command we sent was RETURNED AND ACKNOWLEDGED by Megatron
						if ((CommandPacket.GetCmd() == SLEEP && RobotPacket.GetCmd() == SLEEP) && RobotPacket.GetAck())
						{
							ExeComplete = true;

							CommandSocket.DisconnectTCP();	// Disconnect the CommandSocket

															// Break from the Megatron's grasp
							break;
						}
						else		// Megatron acknowledged our request, let's display what he said
						{
							std::cout << std::endl << "*** Megatron responded with an ACK of: " << RobotPacket.GetAck() << " for our " << cmdTypeEquivalent(RobotPacket.GetCmd())
								<< " command ***" << std::endl << std::endl;
						}
					}
					else
					{
						// We received an incorrect CRC from the Megatron! SABOTAGE!!!
						std::cout << "Incorrect CRC sent by Megatron. Dropping packet!" << RxBuffer;
					}
				}
				else if (RobotPacket.CheckNACK())	// We received a NACK from the Megatron, aka my dating life
				{
					std::cout << "Megatron responded with a NACK!" << std::endl;
				}
				else
				{
					std::cout << "Megatron responded with an unknown error!" << std::endl;
				}
			}
		}
		else
		{
			std::cout << "INVALID COMMAND ENTERED! READ THE INSTRUCTIONS!" << std::endl;
		}
	}
}

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

	// First argument is the function we want to call (aka the logic), arguments thereafter are the ARGUMENTS to that specific function
	std::thread(CommandThreadLogic, argv[1], std::atoi(argv[2])).detach();

	// Telemetry thread will use the same IP address as the command thread. 
	std::thread(TelemetryThreadLogic, argv[1], std::atoi(argv[3])).detach();

	// Loop forever until ExeComplete is true!
	while (!ExeComplete) {}
}