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

#include "sample.h"
#include "OpenNI.h"
#include "NiTE.h"
#include "system_configuration.h"
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
	bool StartRecording(const char *file_name);
	void StopRecording();

	void ConvertJointCoordinateToDepth(nite::Skeleton& skel, nite::JointType joint, float* pOutX, float* pOutY);
	openni::Status ConvertDepthToColor(int depthX, int depthY, uint16_t depthZ, int *pColorX, int *pColorY);
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
	openni::Recorder recorder_;

	std::vector<Sample> sample_buffer_;
	Sample GrabSample_();
private:
};

#endif