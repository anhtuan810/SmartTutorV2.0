//
//  Smart Tutor v2.0
//	SensorReader
//
//  Created: 2015.01.05
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "sensor_reader.h"
#include <iostream>

using namespace nite;
using namespace openni;

Sensor_Reader::Sensor_Reader()
{
}

Sensor_Reader::~Sensor_Reader()
{
}

bool Sensor_Reader::TurnOnOrDie()
{
	this->IsFromFile = true;

	// Initiate environment
	//
	OpenNI::initialize();
	NiTE::initialize();

	// Open devices and streams
	//
	status_openni_ = device_.open(openni::ANY_DEVICE);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_openni_ = depth_stream_.create(device_, SENSOR_DEPTH);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_openni_ = color_stream_.create(device_, SENSOR_COLOR);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_nite_ = user_tracker_.create(&device_);
	if (status_nite_ != nite::STATUS_OK)
		return false;

	// Start the streams
	//
	status_openni_ = color_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_openni_ = depth_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	return true;
}

bool Sensor_Reader::TurnOnOrDie(char* file_name)
{
	this->IsFromFile = true;

	// Initiate environment
	//
	OpenNI::initialize();
	NiTE::initialize();

	// Open devices and streams
	//
	status_openni_ = device_.open(file_name);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_openni_ = depth_stream_.create(device_, SENSOR_DEPTH);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_openni_ = color_stream_.create(device_, SENSOR_COLOR);
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_nite_ = user_tracker_.create(&device_);
	if (status_nite_ != nite::STATUS_OK)
		return false;

	// Start the streams
	//
	status_openni_ = color_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	status_openni_ = depth_stream_.start();
	if (status_openni_ != openni::STATUS_OK)
		return false;

	return true;
}

void Sensor_Reader::TurnOff()
{
	depth_stream_.stop();
	depth_stream_.destroy();
	color_stream_.stop();
	color_stream_.destroy();
	user_tracker_.destroy();
	device_.close();
}

Sample Sensor_Reader::GrabSample_()
{
	VideoFrameRef depth_frame;
	UserTrackerFrameRef user_frame;
	VideoFrameRef color_frame;
	color_stream_.readFrame(&color_frame);
	depth_stream_.readFrame(&depth_frame);
	user_tracker_.readFrame(&user_frame);

	cv::Mat depth_cvmat(SENSOR_FRAME_HEIGHT, SENSOR_FRAME_WIDTH, CV_16U);
	cv::Mat depth_user_cvmat(SENSOR_FRAME_HEIGHT, SENSOR_FRAME_WIDTH, CV_16U);
	cv::Mat color_cvmat(SENSOR_FRAME_HEIGHT, SENSOR_FRAME_WIDTH, CV_8UC3);
	nite::Skeleton skeleton;

	// Draw depth map
	const DepthPixel* pt = (const DepthPixel*)depth_frame.getData();
	std::memcpy(depth_cvmat.data, pt, SENSOR_FRAME_HEIGHT * SENSOR_FRAME_WIDTH * 2);

	// Draw color image
	const char* color_data = (const char*)color_frame.getData();
	std::memcpy(color_cvmat.data, color_data, SENSOR_FRAME_HEIGHT * SENSOR_FRAME_WIDTH * 3);

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
			for (int j = 0; j < SENSOR_FRAME_HEIGHT * SENSOR_FRAME_WIDTH * 2; j++)
			{
				if (label[j / 2] != 0)
					depth_user_cvmat.data[j] = depth_cvmat.data[j];
			}
			contain_user = true;
		}
	}
	cv::flip(color_cvmat, color_cvmat, 1);
	cv::flip(depth_cvmat, depth_cvmat, 1);
	cv::flip(depth_user_cvmat, depth_user_cvmat, 1);

	Sample sample(skeleton, depth_cvmat, depth_user_cvmat, color_cvmat);
	return sample;
}

void Sensor_Reader::QueryFrame()
{
	Sample sample = GrabSample_();
	sample_buffer_.push_back(sample);
	if (sample_buffer_.size() > SENSOR_BUFFER_SIZE)
		sample_buffer_.erase(sample_buffer_.begin());
}

int Sensor_Reader::GetActualBufferSize()
{
	return sample_buffer_.size();
}

Sample Sensor_Reader::GetSampleByIndex(int id)
{
	return sample_buffer_.at(id);
}

std::vector<Sample> Sensor_Reader::GetSampleBuffer()
{
	return sample_buffer_;
}

Sample Sensor_Reader::GetLatestSample()
{
	if (sample_buffer_.size() >= 1)
		return sample_buffer_.at(sample_buffer_.size() - 1);

	else
	{
		Sample sample;
		sample.IsEmpty = true;
		return sample;
	}
}

Sample Sensor_Reader::GetSecondLatestSample()
{
	if (sample_buffer_.size() >= 2)
		return sample_buffer_.at(sample_buffer_.size() - 2);

	else
	{
		Sample sample;
		sample.IsEmpty = true;
		return sample;
	}
}

void Sensor_Reader::ConvertJointCoordinateToDepth(nite::Skeleton& skel, nite::JointType joint, float* pOutX, float* pOutY)
{
	nite::Point3f point = skel.getJoint(joint).getPosition();
	user_tracker_.convertJointCoordinatesToDepth(point.x, point.y, point.z, pOutX, pOutY);
}

openni::Status Sensor_Reader::ConvertDepthToColor(int depthX, int depthY, uint16_t depthZ, int *pColorX, int *pColorY)
{
	std::cout << device_.isImageRegistrationModeSupported(IMAGE_REGISTRATION_DEPTH_TO_COLOR);
	return openni::CoordinateConverter::convertDepthToColor(depth_stream_, color_stream_, depthX, depthY, depthZ, pColorX, pColorY);
}





