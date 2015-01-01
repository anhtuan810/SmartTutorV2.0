//
//  Smart Tutor v1.0
//	Recorder
//
//  Created: 2014.08.13
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#include "kinect_sensor.h"
#include "OpenNI.h"
#include "NiTE.h"
#include "iostream"
#include "sample.h"

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
	depth_stream_.readFrame(&depth_frame);
	user_tracker_.readFrame(&user_frame);

	bool contain_user = false;
	// Check if contain at least one user
	if (user_frame.getUsers().getSize() > 0)
	{
		// Initiate skeleton tracker
		UserData user_data = user_frame.getUsers()[0];
		user_tracker_.startSkeletonTracking(user_data.getId());
		Skeleton skeleton = user_data.getSkeleton();
		if (skeleton.getState() == SkeletonState::SKELETON_TRACKED)
		{
			Sample sample(skeleton);
			return sample;

			//// Draw depth map
			//cv::Mat depth_cvmat(kHeight, kWidth, CV_16U);
			//const DepthPixel* pt = (const DepthPixel*)depth_frame.getData();
			//std::memcpy(depth_cvmat.data, pt, kHeight * kWidth * 2);


			//// Draw depth user map
			//cv::Mat depth_user_cvmat(kHeight, kWidth, CV_16U);
			//depth_user_cvmat = cv::Scalar(0);
			////std::memcpy(depth_user_cvmat.data, depth_cvmat.data, kHeight * kWidth * 2);
			//const UserMap& user_map = user_frame.getUserMap();
			//const UserId* label = user_map.getPixels();
			//for (int j = 0; j < kHeight * kWidth * 2; j++)
			//{
			//	if (label[j / 2] != 0)
			//		depth_user_cvmat.data[j] = depth_cvmat.data[j];
			//}

			//// Write data
			//user_tracked_.push_back(true);
			//skeletons_.push_back(skeleton);
			//depth_user_frames_.push_back(depth_user_cvmat);
			contain_user = true;
		}
	}
	if (!contain_user)
	{
		nite::Skeleton skel;
		//cv::Mat mat;
		//user_tracked_.push_back(false);
		//skeletons_.push_back(skel);
		//depth_user_frames_.push_back(mat);
	}

	Sample sample_failed;
	return sample_failed;
}



char* KinectSensor::GrabFrame()
{
	openni::VideoFrameRef frame;
	color_stream_.readFrame(&frame);

	char* color_data;
	color_data = new char[640 * 480 * 3];
	std::memcpy(color_data, frame.getData(), 640 * 480 * 3);

	return color_data;
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
