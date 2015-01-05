//
//  Smart Tutor v2.0
//	SensorReader
//
//  Created: 2015.01.05
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef SAMPLE_H_
#define SAMPLE_H_

#include <NiTE.h>
#include "opencv2/highgui/highgui.hpp"

class Sample
{
public:
	bool IsEmpty = false;
	bool IsContainUser = false;

	Sample();
	Sample(nite::Skeleton& skel, cv::Mat depth_frame, cv::Mat depth_user_frame, cv::Mat color_frame);
	~Sample();

	nite::Skeleton GetSkeleton();
	nite::Point3f GetJointPosition(nite::JointType joint);
	cv::Mat GetDepthFrame();
	cv::Mat GetDepthUserFrame();
	cv::Mat GetColorFrame();

protected:

private:
	nite::Skeleton skeleton_;
	cv::Mat depth_frame_;
	cv::Mat depth_user_frame_;
	cv::Mat color_frame_;
};

#endif