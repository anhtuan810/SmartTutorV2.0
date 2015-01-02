//
//  Smart Tutor v1.0
//	Recorder
//
//  Created: 
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "sensor_reader.h"
#include "iostream"
#include "sample.h"
#include <opencv\highgui.h>
#include <opencv2\core\core.hpp>

using namespace cv;

void main()
{
	cv::namedWindow("test");

	SensorReader reader("F:\\Development of SmartTutor\\11.oni");
	reader.TurnOnSensor();
	int i = 0;
	while(true)
	{
		reader.QuerrySensor();
		Sample sample = reader.GetLatestSample();
		if (sample.IsContainUser)
			std::cout << i++ << ": " << reader.GetLatestSample().GetJointPosition(nite::JOINT_RIGHT_HAND).x << "\n";
		
		cv::Mat mat = sample.GetColorFrame();
		cv::imshow("test", mat);
		cv::waitKey(30);
	}
	reader.TurnOffSensor();
	

	std::cin.get();
	return;
}