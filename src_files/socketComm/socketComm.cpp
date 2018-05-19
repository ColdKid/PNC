#include "stdafx.h"
#include "socketComm.h"


SocketComm::SocketComm(char* ipAddr, Communication* commu, int ipLength)
{
	_pCommu = commu;
	_ipLength = ipLength;
	initialize(ipAddr);
}

SocketComm::~SocketComm()
{

}

void SocketComm::initialize(char* ipAddr)
{
	_ipAddr = (char*)malloc(_ipLength);
	memset(_ipAddr, 0, _ipLength);
	memset(_sendBuff, 0, sizeof(_sendBuff));
	_ipAddr = ipAddr;
	_peopleNum = 0;
}

BOOLEAN SocketComm::createAndSendSocket()
{
	WSADATA wsaData;
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
	{
		std::cout<<"Failed to load Winsock"<<std::endl;
		return PROCFAILED;
	}

	std::cout << "Connecting to ---->"<< _ipAddr << std::endl;
	SOCKADDR_IN para;
	para.sin_family = AF_INET;
	para.sin_port = htons(5000);
	para.sin_addr.S_un.S_addr = inet_addr(_ipAddr);

	SOCKET socklocal = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == socklocal)
	{
		printf("Socket加载错误");
		getchar();
		return PROCFAILED;
	}

	//向服务器发出连接请求  
	if (connect(socklocal, (struct sockaddr*)&para, sizeof(para)) == INVALID_SOCKET)
	{
		printf("请先连接服务器!");
		getchar();
		return PROCFAILED;
	}
	else
	{
		std::cout << "Connected successfully!" << std::endl;
	}

	while (1)
	{
		//把数据发给服务器
		
		_peopleNum = _pCommu->getNum();
		_itoa(_peopleNum, _sendBuff, 10);
		send(socklocal, _sendBuff, sizeof(_sendBuff), 0);
		Sleep(2000);
	}
	return PROSUCCESS;
}


void SocketComm::run()
{
	createAndSendSocket();
}