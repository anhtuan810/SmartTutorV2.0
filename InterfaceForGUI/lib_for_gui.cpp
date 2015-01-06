//
//  Smart Tutor v2.0
//	Interface for GUI, create dynamic library to link from C++ to C#
//
//  Created: 2015.01.05
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#define HEIGHT 480
#define WIDTH 640

#include "lib_for_gui.h"
#include "sensor_reader.h"
#include "feature_extractor.h"

Sensor_Reader sensor_reader;

bool ITurnOnKinectSensor()
{
	return sensor_reader.TurnOnOrDie();
}

bool ITurnOnONIFile(char* file_name)
{
	return sensor_reader.TurnOnOrDie(file_name);
}

void ITurnOff()
{
	sensor_reader.TurnOff();
}

void IQuerySensor()
{
	sensor_reader.QueryFrame();
}

char* IGrabCurrentColorFrame()
{
	cv::Mat color_frame = sensor_reader.GetLatestSample().GetColorFrame();
	char* data = new char[HEIGHT * WIDTH * 3];
	std::memcpy(data, color_frame.data, WIDTH * HEIGHT * 3);
	return data;
}


//////////////////////////////////////////////////////////////////////////
FeatureExtractor feature_extractor;
void IExtractFeatureNewFrame()
{
	feature_extractor.ProcessNewSample(sensor_reader);
}

int IGetActualFeatureBufferSize()
{
	return feature_extractor.GetActualBufferSize();
}

float* copy_vector(std::vector<float> input)
{
	const int sz = input.size();
	float* data = new float[sz];
	for (size_t i = 0; i < sz; i++)
	{
		data[i] = input[i];
	}
	return data;
}

float* IGetFeature_VelocityLeftHand()
{
	std::vector<float> velocity = feature_extractor.GetVelocity_LeftHand();
	return copy_vector(velocity);
}

float* IGetFeature_VelocityRightHand()
{
	std::vector<float> velocity = feature_extractor.GetVelocity_RightHand();
	return copy_vector(velocity);
}

float* IGetFeature_VelocityGlobal()
{
	std::vector<float> velocity = feature_extractor.GetVelocity_Global();
	return copy_vector(velocity);
}

float* IGetFeature_VelocityFoot()
{
	std::vector<float> velocity = feature_extractor.GetVelocity_Foot();
	return copy_vector(velocity);
}

float* IGetFeature_Energy()
{
	std::vector<float> energy = feature_extractor.GetEnergy();
	return copy_vector(energy);
}

float* IGetFeature_FootStretch()
{
	std::vector<float> stretch = feature_extractor.GetFootStretch();
	return copy_vector(stretch);
}

float* IGetFeature_BalanceBackForth()
{
	std::vector<float> balance = feature_extractor.GetBalanceBackForth();
	return copy_vector(balance);
}

float* IGetFeature_BalanceLeftRight()
{
	std::vector<float> balance = feature_extractor.GetBalanceLeftRight();
	return copy_vector(balance);
}