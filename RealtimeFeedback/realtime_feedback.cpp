#include "realtime_feedback.h"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;

Realtime_Feedback::Realtime_Feedback()
{
}

Realtime_Feedback::~Realtime_Feedback()
{
}

cv::Mat Realtime_Feedback::GetVisualisedFrame(Sensor_Reader& sensor_reader, OverallAssessment& overall_assessment)
{
	Sample sample = sensor_reader.GetLatestSample();
	cv::Mat color_frame = sample.GetColorFrame();
	cv::Mat edge_frame = EdgeDetection_Color(color_frame);

	if (sample.IsContainUser)
	{
		cv::Mat depth_frame = sample.GetDepthFrame();
		cv::Mat user_frame = sample.GetDepthUserFrame();
		cv::Mat user_frame_aligned = Align_Depth(user_frame);
		cv::Mat edge_user_combined = Combine_Edge_n_UserMaps(edge_frame, user_frame_aligned);
		return edge_user_combined;
	}
	else
	{
		return color_frame;
	}
}

cv::Mat Realtime_Feedback::EdgeDetection_Color(cv::Mat& color_frame)
{
	// Convert to gray
	cv::Mat gray_frame(color_frame.size(), CV_8UC1);
	gray_frame = cv::Scalar(0);
	cvtColor(color_frame, gray_frame, CV_BGR2GRAY);

	// Perform Canny edge detection
	cv::Mat detected_edges;
	cv::blur(gray_frame, detected_edges, Size(10, 10));
	int low_threshold = 10;
	float ratio = 3;
	int kernel_size = 3;
	Canny(detected_edges, detected_edges, low_threshold, low_threshold * ratio, kernel_size);

	// Return
	return detected_edges;
}

cv::Mat Realtime_Feedback::Align_Depth(cv::Mat& user_frame)
{
	float ratio_h = 0.91;
	float ratio_w = 0.91;
	cv::Mat user_frame_2(user_frame.size(), user_frame.type());
	user_frame_2 = Scalar(0);
	int centerH = 240;
	int centerW = 320;
	for (size_t h = 0; h < 480; h++)
	{
		for (size_t w = 0; w < 640; w++)
		{
			uint16_t depth = user_frame.at<uint16_t>(h, w);
			if (depth != 0)
			{
				int dH = h - centerH;
				int dW = w - centerW;
				dH *= ratio_h;
				dW *= ratio_w;
				int newH = centerH + dH;
				int newW = centerW + dW;
				if (newH < 0) newH = 0;
				if (newW < 0) newW = 0;
				if (newH > 479) newH = 479;
				if (newW > 639) newW = 639;
				user_frame_2.at<uint16_t>(newH, newW) = depth;
			}
		}
	}
	return user_frame_2;
}

cv::Mat Realtime_Feedback::Combine_Edge_n_UserMaps(cv::Mat& edge_frame, cv::Mat& user_frame)
{
	cv::Mat combined_frame(edge_frame.size(), CV_8UC3);
	combined_frame = Scalar(0);
	for (size_t h = 0; h < 480; h++)
	{
		for (size_t w = 0; w < 640; w++)
		{
			Point3_<uchar>* p = combined_frame.ptr<Point3_<uchar> >(h, w);
			p->x = p->y = p->z = 10;
			if (edge_frame.at<uchar>(h, w) != 0)
			{
				p->x = 100; // B
				p->y = 100; // G
				p->z = 255; // R
			}
		}
	}

	cv::blur(combined_frame, combined_frame, cv::Size(5, 5));
	//int erosion_size = 1;
	//cv::Mat element = cv::getStructuringElement(cv::MORPH_ELLIPSE, cv::Size(erosion_size * 2 + 1, erosion_size * 2 + 1), cv::Point(erosion_size, erosion_size));
	//cv::erode(user_frame, user_frame, element);

	for (size_t h = 0; h < 480; h++)
	{
		for (size_t w = 0; w < 640; w++)
		{
			Point3_<uchar>* p = combined_frame.ptr<Point3_<uchar> >(h, w);
			uint16_t depth = user_frame.at<uint16_t>(h, w);
			if (depth != 0)
			{
				//p->x = (uchar)(((float)255 / range) * (max - depth));
				p->x = (uchar)(depth / 20);
				p->y = (uchar)(depth / 20);
				p->z = (uchar)(depth / 20);
			}
		}
	}

	return combined_frame;
}
