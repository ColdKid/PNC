#ifndef _COMMUNICATION_IF_
#define _COMMUNICATION_IF_
#include "stdafx.h"
#include <vector>
#include <iostream>
#include <opencv2/opencv.hpp> 
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> 
#include <mutex>
#include <windows.h>
#include <queue>
#include "commonDef.h"

class Communication
{
public:
	Communication();
	~Communication();

	BOOLEAN sendContent(cv::Mat content);
	BOOLEAN getContent(cv::Mat &frame);
	inline BOOLEAN sendFaceLoc(std::vector<cv::Rect> faces){ _faces = faces; return PROSUCCESS;}
	inline BOOLEAN getFaceLoc(std::vector<cv::Rect>& faces){ faces = _faces; return PROSUCCESS; }
	inline BOOLEAN storeNum(int num){ _peoNum = num; return PROSUCCESS; }
	inline int getNum(){ return _peoNum; }

private:

	std::mutex _mtx;
	std::queue<cv::Mat> _frameQue;
	std::vector<cv::Rect> _faces;
	int _peoNum;
	/*用于单件自动删除的内部类*/
	//class Delete
	//{
	//public:
	//	Delete(){}
	//	~Delete(){ delete _pInstance; }
	//};
};

#endif /*_COMMUNICATION_IF_*/
