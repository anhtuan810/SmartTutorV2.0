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
	cv::Mat color_frame = sensor_reader.GetLastSample().GetColorFrame();
	char* data = new char[HEIGHT * WIDTH * 3];
	std::memcpy(data, color_frame.data, WIDTH * HEIGHT * 3);
	return data;
}