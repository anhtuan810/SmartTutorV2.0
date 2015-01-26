#ifndef REALTIME_FEEDBACK_H_
#define REALTIME_FEEDBACK_H_

#include "sensor_reader.h"
#include "overall_assessment.h"
#include "opencv2/core/core.hpp"
#include <vector>

class Realtime_Feedback
{
public:
	Realtime_Feedback();
	Realtime_Feedback(Sensor_Reader &sensor_reader, OverallAssessment &overall_assessment);
	~Realtime_Feedback();

	void SetSensorReader(Sensor_Reader& sensor_reader);
	void SetOverallAssessment(OverallAssessment& overall_assessment);

	cv::Mat GetVisualisedFrame();
	std::vector<nite::Point3f> GetPoints_to_Annotate();

private:
	Sensor_Reader* sensor_reader_;
	OverallAssessment* overall_assessment_;

	cv::Mat EdgeDetection_Color(cv::Mat& color_frame);
	cv::Mat Align_Depth(cv::Mat& user_frame);
	cv::Mat Combine_Edge_n_UserMaps(cv::Mat& edge_frame, cv::Mat& user_frame);
};

#endif // !REALTIME_FEEDBACK_H_