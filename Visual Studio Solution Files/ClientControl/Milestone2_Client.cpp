#include <iostream>
#include "../MySocket.h"

int main()
{
	std::cout << "=== Client ===" << std::endl << std::endl;

	MilestoneTwo::MySocket TCPClientSocket(SocketType::CLIENT, "127.0.0.1", 5000, ConnectionType::TCP, 100);

	std::string TCPPkt = "I love BTN415 - Sent by TCP Client";

	TCPClientSocket.ConnectTCP();
	TCPClientSocket.SendData(TCPPkt.c_str(), strlen(TCPPkt.c_str())+1);

	char buff[100];
	int RxSize = TCPClientSocket.GetData(buff);

	std::cout << "Msg = " << buff << ", Bytes = " << RxSize << std::endl;

	TCPClientSocket.DisconnectTCP();

	memset(buff, 0, sizeof(buff));
	RxSize = 0;

	MilestoneTwo::MySocket UDPClientSocket(SocketType::CLIENT, "127.0.0.1", 9001, ConnectionType::UDP, 100);

	std::string UDPPkt = "I love BTN415 - Sent by UDP Client";

	UDPClientSocket.ConnectTCP();	// Should not work!
	UDPClientSocket.SendData(UDPPkt.c_str(), strlen(UDPPkt.c_str()) + 1);

	RxSize = UDPClientSocket.GetData(buff);

	std::cout << "Msg = " << buff << ", Bytes = " << RxSize << std::endl;

	std::cin.get();

	return 1;
}
