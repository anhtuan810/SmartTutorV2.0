#include "lib_for_gui.h"
#include "sensor_reader.h"
#include "overall_assessment.h"
#include "realtime_feedback.h"
#include "feature_extractor.h"
#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;


void main()
{
	Sensor_Reader sensor_reader;
	sensor_reader.TurnOnOrDie("G:\\Development of SmartTutor\\11.oni");
	FeatureExtractor feature_extractor(sensor_reader);
	OverallAssessment overall_assessment(feature_extractor);
	Realtime_Feedback realtime_feedback;
	realtime_feedback.SetSensorReader(sensor_reader);
	realtime_feedback.SetOverallAssessment(overall_assessment);

	cv::namedWindow("test");
	while (true)
	{
		sensor_reader.QueryFrame();
		cv::imshow("test", sensor_reader.GetLatestSample().GetColorFrame());
		cv::waitKey(30);

		feature_extractor.ProcessNewSample();
		overall_assessment.PerformAssessment();

		std::cout << overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Balance_LeaningLeft).size();
	}
}

void main1()
{
	Sensor_Reader sensor_reader;
	sensor_reader.TurnOnOrDie("G:\\Development of SmartTutor\\11.oni");
	OverallAssessment overall_assessment;
	Realtime_Feedback realtime_feedback;
	realtime_feedback.SetSensorReader(sensor_reader);
	realtime_feedback.SetOverallAssessment(overall_assessment);

	cv::namedWindow("test1");

	while (true)
	{
		sensor_reader.QueryFrame();
		cv::Mat edge_frame = realtime_feedback.GetVisualisedFrame();
		
		// Post process combined image
		cv::Mat larger_frame;
		cv::resize(edge_frame, larger_frame, cv::Size(640 * 2, 480 * 2));
		//cv::blur(larger_frame, larger_frame, cv::Size(5, 5));

		std::vector<nite::Point3f> points = realtime_feedback.GetPoints_to_Annotate();
		
		Sample sample = sensor_reader.GetLatestSample();
		if (sample.IsContainUser)
		{
			nite::Point3f point = sensor_reader.GetLatestSample().GetJointPosition(nite::JOINT_LEFT_HAND);
			float x, y;
			sensor_reader.ConvertJointCoordinateToDepth(sample.GetSkeleton(), nite::JOINT_LEFT_HAND, &x, &y);
			//std::cout << x << " -- " << y << "\n";
		}
		cv::imshow("test1", larger_frame);
		
		cv::waitKey(30);
	}
}