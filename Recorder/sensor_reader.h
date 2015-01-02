#ifndef SENSOR_READER_H
#define SENSOR_READER_H

#include "kinect_sensor.h"
#include "sample.h"
#include <vector>

class SensorReader
{
public:
	bool IsFromFile;

	SensorReader();
	SensorReader(char* file_name);
	~SensorReader();

	void SetBufferSize(int buff_size);
	void TurnOnSensor();
	void QuerrySensor();
	void TurnOffSensor();

	Sample GetLatestSample();
	std::vector<Sample> GetSamplesBuffer();
	cv::Mat GetLatestColorFrame();

protected:

private:
	KinectSensor sensor_;
	char* file_name_;
	int buffer_size_ = 100;
	Sample latest_sample_;
	std::vector<Sample> sample_buffer_;
};

#endif