// PNC.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "detectProcess.h"
#include "camCatch.h"
#include "socketComm.h"
#include <thread>


template<typename T>
void freePoint(T pInsPoint)
{
	if (pInsPoint != nullptr)
	{
		delete pInsPoint;
		pInsPoint = nullptr;
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	BOOLEAN socketFlag = false;
	char* ip = (char*)malloc(15);
	int length = 0;
	int choice = 0;
	
	std::cout << "\n*********************** PNC system launched! ***********************\n" << std::endl;
	//队列对象
	Communication *pCommu = new Communication();
	//检测和摄像对象
	DetetProcess *dete = new DetetProcess(pCommu);
	Camera *camer = new Camera(pCommu);
	SocketComm* socketCom = nullptr;

	std::cout << "是否连接服务器：1.yes 2.no" << std::endl;
	
	std::cin >> choice;
	switch (choice)
	{
	case 1:
		std::cout << "输入服务器ip：" << std::endl;
		std::cin >> ip;
		GET_CHAR_SIZE(ip, length);
		socketCom = new SocketComm(ip, pCommu,length);
		socketFlag = true;
		break;
	case 2:
		break;
	default:
		std::cout << "wrong choice!" << std::endl;
		break;
	}

	std::thread *threadCame = new std::thread(&Camera::run, camer);
	Sleep(2000);//等待摄像线程先起
	
	std::thread *threadDete = new std::thread(&DetetProcess::run, dete);

	std::thread *threadSocketCom = nullptr;
	if (socketFlag)
	{
		threadSocketCom = new std::thread(&SocketComm::run, socketCom);
	}
	
	threadCame->join();
	//Sleep(1000);
	threadDete->join();
	if (socketFlag)
	{
		threadSocketCom->join();
	}
	cvWaitKey();
	freePoint(dete);
	freePoint(camer);
	freePoint(socketCom);
	return 0;
}

