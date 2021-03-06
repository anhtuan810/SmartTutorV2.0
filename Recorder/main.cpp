#include "sensor_reader.h"
#include "iostream"
#include "sample.h"
#include <opencv\highgui.h>
#include <opencv2\core\core.hpp>

using namespace cv;

void main1()
{
	cv::namedWindow("test");
	Sensor_Reader sensor;
	sensor.TurnOnOrDie();
	sensor.StartRecording("G:\\test.oni");
	cv::waitKey(300);
	sensor.TurnOff();
}


void main()
{
	cv::namedWindow("test");
	Sensor_Reader sensor;
	sensor.TurnOnOrDie("G:\\Development of SmartTutor\\11.oni");
	//sensor.TurnOnOrDie();

	int i = 0;
	while(true)
	{
		sensor.QueryFrame();
		Sample sample = sensor.GetLatestSample();
		if (sample.IsContainUser)
			std::cout << i++ << ": " << sensor.GetLatestSample().GetJointPosition(nite::JOINT_RIGHT_HAND).x << "\n";
		
		cv::Mat mat = sample.GetColorFrame();
		cv::imshow("test", mat);
		cv::waitKey(30);
	}
	sensor.TurnOff();
	

	std::cin.get();
	return;
}