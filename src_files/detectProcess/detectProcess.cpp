#include "stdafx.h"
#include "detectProcess.h"


DetetProcess::DetetProcess(Communication* pCommu) : _pCommu(pCommu)
{
	_peoNum = 0;
}

DetetProcess::~DetetProcess()
{

}

void DetetProcess::run()
{
	std::string cascadeDire = ".\\cascade\\haarcascade_frontalface_alt2.xml";
	cv::Mat tempFrame/* = cv::imread("test.jpg")*/;
	cv::CascadeClassifier cascade;
	if (!cascade.load(cascadeDire))
	{
		printf("cascade load failed!");
		return;
	}
	while (1)
	{
		_pCommu->getContent(tempFrame);
		doDetect(tempFrame, cascade);
	}
	return;
}

//检测函数
BOOLEAN DetetProcess::doDetect(cv::Mat img, cv::CascadeClassifier cascade)
{
	//预处理图像
	cv::cvtColor(img, _imgGray, cv::COLOR_BGR2GRAY);
	cv::resize(_imgGray, _imgGray, _imgGray.size(), 0, 0, cv::INTER_LINEAR);    //用双线性插值进行图像调整
	cv::equalizeHist(_imgGray, _imgEqulize);
	cv::GaussianBlur(_imgEqulize, _imgGaussian, cv::Size(3, 3), 0, 0);

	//检测并保存矩形至向量数组中

	std::vector<cv::Rect> faces;
	cascade.detectMultiScale(_imgGaussian, faces, 1.1, 2, CV_HAAR_DO_CANNY_PRUNING/*, cv::Size(30, 30)*/);
#if 0
	for (unsigned int i = 0; i < faces.size(); i++)
	{
		cv::Point pt2(faces[i].x, faces[i].y);
		cv::Point pt1(faces[i].x + faces[i].width, faces[i].y + faces[i].height);
		cv::rectangle(img, pt1, pt2, 245, 3, 8, 0);
	}
#endif
	_pCommu->sendFaceLoc(faces);
	//获取当前人数
	_peoNum = static_cast<int>(faces.size());

	//显示窗口
	//cv::namedWindow("show resault");
	//cv::imshow("show resault", img);
	cv::waitKey(1);
	std::cout << "current people num:" << _peoNum << std::endl;
	return PROSUCCESS;
}

int DetetProcess::getPeoNum()
{
	return _peoNum;
}
