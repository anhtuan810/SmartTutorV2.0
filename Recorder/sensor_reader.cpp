#define BUFFER_SIZE 100

#include "sensor_reader.h"


SensorReader::SensorReader()
{
	this->IsFromFile = false;
}

SensorReader::SensorReader(char* file_name)
{
	this->IsFromFile = true;
	file_name_ = file_name;
}


SensorReader::~SensorReader()
{

}

void SensorReader::QuerrySensor()
{
	latest_sample_ = sensor_.Querry();
	sample_buffer_.push_back(latest_sample_);
	if (sample_buffer_.size() > buffer_size_)
		sample_buffer_.erase(sample_buffer_.begin());
}

Sample SensorReader::GetLatestSample()
{
	return latest_sample_;
}

std::vector<Sample> SensorReader::GetSamplesBuffer()
{
	return sample_buffer_;
}

void SensorReader::TurnOnSensor()
{
	if (this->IsFromFile)
		sensor_.SetFileName(file_name_);

	sensor_.TurnOnOrDie();
}

void SensorReader::TurnOffSensor()
{
	sensor_.TurnOff();
}

void SensorReader::SetBufferSize(int buff_size)
{
	buffer_size_ = buff_size;
}
