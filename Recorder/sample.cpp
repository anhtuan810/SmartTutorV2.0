#include "sample.h"

using namespace nite;

Sample::Sample()
{
	this->IsContainUser = false;
}

Sample::~Sample()
{

}

Sample::Sample(nite::Skeleton& skel, cv::Mat depth_frame, cv::Mat depth_user_frame, cv::Mat color_frame)
{
	depth_frame_ = depth_frame;
	depth_user_frame_ = depth_user_frame;
	color_frame_ = color_frame;

	if (skel.getState() != SKELETON_TRACKED)
	{
		this->IsContainUser = false;
	}
	else
	{
		this->IsContainUser = true;
		skeleton_ = skel;
	}
}

nite::Skeleton Sample::GetSkeleton()
{
	return skeleton_;
}

nite::Point3f Sample::GetJointPosition(nite::JointType joint)
{
	return skeleton_.getJoint(joint).getPosition();
}

cv::Mat Sample::GetDepthFrame()
{
	return depth_frame_;
}

cv::Mat Sample::GetColorFrame()
{
	return color_frame_;
}

cv::Mat Sample::GetDepthUserFrame()
{
	return depth_user_frame_;
}
