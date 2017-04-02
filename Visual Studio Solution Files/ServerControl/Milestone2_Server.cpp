#include "../MySocket.h"

int main()
{
	std::cout << "=== Server ===" << std::endl << std::endl;

	MilestoneTwo::MySocket TCPServerSocket(SocketType::SERVER, "127.0.0.1", 5000, ConnectionType::TCP, 100);

	char buff[100];

	int RxSize = TCPServerSocket.GetData(buff);

	std::cout << "Msg = " << buff << ", Bytes = " << RxSize << std::endl;

	/* None of the 4 setters below should work */
	TCPServerSocket.SetIPAddr("Name");
	TCPServerSocket.SetPortNo(9001);
	TCPServerSocket.SetType(CLIENT);

	std::string TCPPkt = "I love BTN415 too - Sent by TCP Server";

	TCPServerSocket.SendData(TCPPkt.c_str(), strlen(TCPPkt.c_str())+1);

	TCPServerSocket.DisconnectTCP();

	memset(buff, 0, sizeof(buff));
	RxSize = 0;

	MilestoneTwo::MySocket UDPServerSocket(SocketType::SERVER, "127.0.0.1", 9001, ConnectionType::UDP, 100);

	std::string UDPPkt = "I love BTN415 too - Sent by UDP Server";

	RxSize = UDPServerSocket.GetData(buff);

	UDPServerSocket.SetIPAddr("255.255.255.255");
	UDPServerSocket.SetPortNo(5000);
	UDPServerSocket.SetType(SERVER);

	/* Note: The server program will finish but the client will forever be waiting for data because we called GetData() but here
		we sent the data to a random IP Address of 255.255.2555.255 and Port number 5000 */
	UDPServerSocket.SendData(UDPPkt.c_str(), strlen(UDPPkt.c_str()) + 1);

	std::cout << "Msg = " << buff << ", Bytes = " << RxSize << std::endl;

	std::cin.get();

	return 1;
}
