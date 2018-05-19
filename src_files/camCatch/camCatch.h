#ifndef CAMERA
#define CAMERA
#include "stdafx.h"
#include<opencv2/opencv.hpp> 
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp> 
#include<iostream> 
#include <vector>
#include <mutex>
#include "communicationIf.h"

class Camera
{
public:
	Camera(Communication* pCommu);
	~Camera();

	void run();
	//获取帧的接口函数
private:
	//bool launchCam();
	std::mutex _mtx;
	std::vector<cv::Mat> _catchFrame;
	//int pushImgToVec(cv::Mat frame);
	Communication* _pCommu;
	std::vector<cv::Rect> _faces;
};


#endif /*CAMERA*/