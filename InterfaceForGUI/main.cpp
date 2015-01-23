#include "lib_for_gui.h"
#include "sensor_reader.h"
#include "overall_assessment.h"
#include "realtime_feedback.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;


void main()
{
	Sensor_Reader sensor_reader;
	OverallAssessment overall_assessment;
	Realtime_Feedback realtime_feedback;

	sensor_reader.TurnOnOrDie("G:\\Development of SmartTutor\\11.oni");
	cv::namedWindow("test1");

	while (true)
	{
		sensor_reader.QueryFrame();
		cv::Mat edge_frame = realtime_feedback.GetVisualisedFrame(sensor_reader, overall_assessment);
		

		// Post process combined image
		cv::Mat larger_frame;
		cv::resize(edge_frame, larger_frame, cv::Size(640 * 2, 480 * 2));
		//cv::blur(larger_frame, larger_frame, cv::Size(5, 5));




		cv::imshow("test1", larger_frame);
		
		cv::waitKey(30);
	}
}