//
//  Smart Tutor v2.0
//	SensorReader
//
//  Created: 2015.01.05
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef SENSOR_READER_H_
#define SENSOR_READER_H_

#define HEIGHT 480
#define WIDTH 640
#define BUFFER_SIZE 100

#include "sample.h"
#include "OpenNI.h"
#include "NiTE.h"
#include <vector>

class Sensor_Reader
{
public:
	bool IsFromFile;

	Sensor_Reader();
	~Sensor_Reader();

	bool TurnOnOrDie();
	bool TurnOnOrDie(char* file_name);
	void TurnOff();
	void QueryFrame();

	Sample GetLatestSample();
	Sample GetSecondLatestSample();
	int GetActualBufferSize();
	Sample GetSampleByIndex(int id);
	std::vector<Sample> GetSampleBuffer();

private:
	openni::Status status_openni_;
	nite::Status status_nite_;
	nite::UserTracker user_tracker_;
	openni::Device device_;
	openni::VideoStream depth_stream_;
	openni::VideoStream color_stream_;

	std::vector<Sample> sample_buffer_;
	Sample GrabSample_();
private:
};

#endif