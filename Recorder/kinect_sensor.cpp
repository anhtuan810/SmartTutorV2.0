//
//  Smart Tutor v1.0
//	Recorder
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#define WIDTH 640
#define HEIGHT 480

#include "kinect_sensor.h"
#include "OpenNI.h"
#include "NiTE.h"
#include "iostream"
#include "sample.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace openni;
using namespace nite;

KinectSensor::KinectSensor()
{
	this->IsFromFile = false;
}


KinectSensor::KinectSensor(char* file_name)
{
	this->IsFromFile = true;
	file_name_ = file_name;
}


KinectSensor::~KinectSensor()
{
	depth_stream_.destroy();
	color_stream_.destroy();
	if (recorder_.isValid()) 
		recorder_.destroy();
}


bool KinectSensor::TurnOnOrDie()
{
	openni::Status openni_status = OpenNI::initialize();
	nite::Status nite_status = NiTE::initialize();

	if (this->IsFromFile)
		openni_status = device_.open(file_name_);
	else
		openni_status = device_.open(openni::ANY_DEVICE);
	if (openni_status != openni::STATUS_OK)
		return false;

	openni_status = depth_stream_.create(device_, SENSOR_DEPTH);	
	if (openni_status != openni::STATUS_OK)
		return false;
	depth_stream_.start();

	openni_status = color_stream_.create(device_, SENSOR_COLOR);
	if (openni_status != openni::STATUS_OK)
		return false;
	color_stream_.start();

	nite_status = user_tracker_.create(&device_);
	if (nite_status != nite::STATUS_OK)
		return false;

	openni_status = depth_stream_.start();
	if (openni_status != openni::STATUS_OK)
		return false;

	return true;
}


Sample KinectSensor::Querry()
{
	VideoFrameRef depth_frame;
	UserTrackerFrameRef user_frame;
	VideoFrameRef color_frame;
	color_stream_.readFrame(&color_frame);
	depth_stream_.readFrame(&depth_frame);
	user_tracker_.readFrame(&user_frame);

	cv::Mat depth_cvmat(HEIGHT, WIDTH, CV_16U);
	cv::Mat depth_user_cvmat(HEIGHT, WIDTH, CV_16U);
	cv::Mat color_cvmat(HEIGHT, WIDTH, CV_8UC3);
	nite::Skeleton skeleton;

	// Draw depth map
	const DepthPixel* pt = (const DepthPixel*)depth_frame.getData();
	std::memcpy(depth_cvmat.data, pt, HEIGHT * WIDTH * 2);
	
	// Draw color image
	const char* color_data = (const char*)color_frame.getData();
	for (size_t i = 0; i < 640 * 480 * 3 - 3; i+=3)
	{
		color_cvmat.data[i] = color_data[i + 2];
		color_cvmat.data[i + 1] = color_data[i + 1];
		color_cvmat.data[i + 2] = color_data[i];
	}

	// Check if contain at least one user
	bool contain_user = false;
	if (user_frame.getUsers().getSize() > 0)
	{
		// Initiate skeleton tracker
		UserData user_data = user_frame.getUsers()[0];
		user_tracker_.startSkeletonTracking(user_data.getId());
		skeleton = user_data.getSkeleton();
		if (skeleton.getState() == SkeletonState::SKELETON_TRACKED)
		{
			// Draw depth user map
			depth_user_cvmat = cv::Scalar(0);
			//std::memcpy(depth_user_cvmat.data, depth_cvmat.data, kHeight * kWidth * 2);
			const UserMap& user_map = user_frame.getUserMap();
			const UserId* label = user_map.getPixels();
			for (int j = 0; j < HEIGHT * WIDTH * 2; j++)
			{
				if (label[j / 2] != 0)
					depth_user_cvmat.data[j] = depth_cvmat.data[j];
			}
			contain_user = true;
		}
	}

	Sample sample(skeleton, depth_cvmat, depth_user_cvmat, color_cvmat);
	return sample;
}

void KinectSensor::TurnOff()
{
	depth_stream_.stop();
	depth_stream_.destroy();
	color_stream_.stop();
	color_stream_.destroy();
	device_.close();
}

void KinectSensor::SetFileName(char* file_name)
{
	file_name_ = file_name;
	this->IsFromFile = true;
}
