#ifndef DETECT_PROCESS
#define DETECT_PROCESS

#include "stdafx.h"
#include <highgui.h>
#include <cv.h>
#include <stdio.h>
#include <string>
#include "communicationIf.h"
#include "commonDef.h"

class DetetProcess
{
public:
	DetetProcess(Communication* pCommu);
	~DetetProcess();
	void run();
	int getPeoNum();
	inline std::vector<cv::Rect> getFacesLoc(){ return _faces; }
private:
	int _peoNum;
	cv::Mat _imgGray;
	cv::Mat _imgEqulize;
	cv::Mat _imgGaussian;
	std::vector<cv::Rect> _faces;
	BOOLEAN doDetect(cv::Mat img, cv::CascadeClassifier cascade);
	void deleRepeat();
private:
	Communication* _pCommu;
};

#endif /*DETECT_PROCESS*/