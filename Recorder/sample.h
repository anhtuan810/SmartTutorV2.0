#ifndef SENSOR_SAMPLE_H
#define SENSOR_SAMPLE_H

#include <NiTE.h>
#include "opencv2/highgui/highgui.hpp"

class Sample
{
public:
	bool IsContainUser;

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