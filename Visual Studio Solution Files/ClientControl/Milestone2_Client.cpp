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

	/* None of the 4 setters below should work */
	TCPClientSocket.SetConnType(UDP);
	TCPClientSocket.SetIPAddr("Hello");
	TCPClientSocket.SetPortNo(100);
	TCPClientSocket.SetType(SERVER);

	TCPClientSocket.DisconnectTCP();

	memset(buff, 0, sizeof(buff));
	RxSize = 0;

	MilestoneTwo::MySocket UDPClientSocket(SocketType::CLIENT, "127.0.0.1", 9001, ConnectionType::UDP, 100);

	std::string UDPPkt = "I love BTN415 - Sent by UDP Client";

	/* ConnectTCP() should NOT work for a UDP connection */
	UDPClientSocket.ConnectTCP();
	UDPClientSocket.SendData(UDPPkt.c_str(), strlen(UDPPkt.c_str()) + 1);

	/* None of the 4 setters below should work */
	UDPClientSocket.SetConnType(TCP);
	UDPClientSocket.SetIPAddr("My");
	UDPClientSocket.SetPortNo(350);
	UDPClientSocket.SetType(CLIENT);

	RxSize = UDPClientSocket.GetData(buff);

	std::cout << "Msg = " << buff << ", Bytes = " << RxSize << std::endl;

	std::cin.get();

	return 1;
}
