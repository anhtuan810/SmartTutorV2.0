#include "lib_for_gui.h"
#include "sensor_reader.h"
#include <iostream>

void main()
{
	Sensor_Reader sensor_reader;
	sensor_reader.TurnOnOrDie();
	sensor_reader.QueryFrame();
	cv::Mat color_frame = sensor_reader.GetLastSample().GetColorFrame();
	char* data = new char[HEIGHT * WIDTH * 3];
	std::memcpy(data, color_frame.data, WIDTH * HEIGHT * 3);

	std::cin.get();
}