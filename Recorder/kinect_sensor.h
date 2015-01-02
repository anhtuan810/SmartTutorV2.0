//
//  Smart Tutor v2.0
//	Recorder
//
//  Created: 2015.01.01
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef KINECT_SENSOR_H
#define KINECT_SENSOR_H

#include "OpenNI.h"
#include <NiTE.h>
#include "sample.h"

class KinectSensor
{
public:
	bool IsFromFile;

	KinectSensor();
	KinectSensor(char* file_name);
	~KinectSensor();

	void SetFileName(char* file_name);
	bool TurnOnOrDie();
	void TurnOff();
	Sample Querry();

protected:
private:
	openni::Status status_openni_;
	openni::Device device_;
	openni::VideoStream depth_stream_;
	openni::VideoStream color_stream_;
	openni::Recorder recorder_;
	char* file_name_;
	nite::UserTracker user_tracker_;
};

#endif