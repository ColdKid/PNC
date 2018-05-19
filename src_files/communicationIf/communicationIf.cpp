#include "stdafx.h"
#include "communicationIf.h"


Communication::Communication()
{
}

Communication::~Communication()
{
}


BOOLEAN Communication::sendContent(cv::Mat frame)
{
	//std::cout << "in send content" << _frameQue.size() << std::endl;
	//Ëø°²È«
	if (_mtx.try_lock())
	{
		if (_frameQue.size() <= MAXQUEUENUM)
		{
			//std::lock_guard<std::mutex> guard(_mtx);
			_frameQue.push(frame);
		}
		//std::cout << "pushback mat! size:" << _frameQue.size() << std::endl;
		_mtx.unlock();
		Sleep(100);
	}
	else
	{
		std::cout << "Error: lock param failed when try to write data!" << std::endl;
		return PROCFAILED;
	}
	return PROSUCCESS;
}

BOOLEAN Communication::getContent(cv::Mat &frame)
{
	//std::cout << "in getContent" << _frameQue.size() << std::endl;

	if (_mtx.try_lock())
	{
		//std::cout << "Locked: the vector is locked! size:" << _frameQue.size() << std::endl;
		if (!_frameQue.empty())
		{
			frame = _frameQue.front();
			_frameQue.pop();
			_mtx.unlock();
			return PROSUCCESS;
		}
		else
		{
			std::cout << "Warning: the vector is empty!" << std::endl;
		}
		_mtx.unlock();
	}
	else
	{
		std::cout << "Error: lock param failed when try to read data!" << std::endl;
	}
	return PROCFAILED;
}