#include "lib_for_gui.h"
#include "sensor_reader.h"
#include <iostream>

void main()
{
	SensorReader reader("F:\\Development of SmartTutor\\11.oni");
	reader.TurnOnSensor();
	reader.QuerrySensor();

	cv::Mat color_frame = reader.GetLatestColorFrame();
	char* data = new char[640 * 480 * 3];
	std::memcpy(data, color_frame.data, 640 * 480 * 3);

	std::cin.get();
}