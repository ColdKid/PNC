#ifndef SOCKET_COMM
#define SOCKET_COMM

#include "stdafx.h"

#include <WinSock2.h>
#include <windows.h>
#include <iostream>
#include "commonDef.h"
#include "communicationIf.h"

class SocketComm
{
public:
	SocketComm(char* ipAddr, Communication* commu, int ipLength);
	~SocketComm();
	void initialize(char* ipAddr);
	void run();

private:
	BOOLEAN createAndSendSocket();
	char* _ipAddr;
	int _ipLength;
	char _sendBuff[2];
	int _peopleNum;
	Communication* _pCommu;
};



#endif  /*SOCKET_COMM*/