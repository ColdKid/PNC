#include "stdafx.h"
#include "camCatch.h"

Camera::Camera(Communication* pCommu) : _pCommu(pCommu)
{
	_faces.clear();
}

Camera::~Camera()
{

}

void Camera::run()
{
	cv::VideoCapture capture(0);
	cv::Mat camPicFrame;
	cv::string winName = "Detect";
	cv::Point pt2;
	if (!capture.isOpened())
	{
		std::cout << "Error: Camera launch failed!" << std::endl;
		return;
	}
	/*设置视频采集分辨率为640x480，30fps*/
	capture.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	capture.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	capture.set(CV_CAP_PROP_FPS, 30.0);
	cv::namedWindow(winName);
	while (1)
	{
		capture >> camPicFrame;
		if (camPicFrame.empty())
		{
			std::cout << "Error: the captured frame is null." << std::endl;
			break;
		}
		_pCommu->sendContent(camPicFrame);
		cv::waitKey(30);
		
		_pCommu->getFaceLoc(_faces);
		_pCommu->storeNum(static_cast<int>(_faces.size()));
		//std::cout << faces.size() << std::endl;
		for (unsigned int i = 0; i < _faces.size(); i++)
		{
			cv::Point pt2(_faces[i].x, _faces[i].y);
			cv::Point pt1(_faces[i].x + _faces[i].width, _faces[i].y + _faces[i].height);
			cv::rectangle(camPicFrame, pt1, pt2, 245, 1, 8, 0);
		}
		cv::imshow(winName, camPicFrame);

	}

	return;
}

