//
//  Smart Tutor v1.0
//	InterfaceForGUI
//
//  Created: 2014.08.14
//
//  Copyright (c) 2014 Anh Tuan Nguyen. All rights reserved.
//
#define HEIGHT 480
#define WIDTH 640

#include "lib_for_gui.h"
#include "sensor_reader.h"


SensorReader sensor_reader;

//bool IStartRecordingONI(char* file_name)
//{
//	return sensor_.StartRecordingOrDie(file_name);
//}
//
//void IStopRecordingONI()
//{
//	sensor_.StopRecording();
//}

bool ITurnOnKinectSensor()
{
	sensor_reader.TurnOnSensor();
	return true;
}

//void ITurnOffKinectSensor()
//{
//	sensor_.TurnOff();
//}
//
char* IGrabFrame()
{
	cv::Mat color_frame = sensor_reader.GetLatestColorFrame();
	char* data = new char[HEIGHT * WIDTH * 3];
	std::memcpy(data, color_frame.data, WIDTH * HEIGHT * 3);
	return data;
}

void IQuerrySensor()
{
	sensor_reader.QuerrySensor();
}

//
//
//
//
//FeatureAnalyser feature_analyser_;
//AssessmentOverall scorer_;
//
//bool IGenerateFeaturesFromONI(char* ONI_file_name, char* data_folder)
//{
//	ONIReader reader;
//	reader.ReadONI(ONI_file_name);
//	FeatureExtractor feature_extractor;
//	feature_extractor.ReceiveONIReader_n_Process(reader.depth_user_frames_, reader.skeletons_, reader.user_tracked_, reader.frame_no_);
//	feature_extractor.Save_2_Files(data_folder);
//	return true;
//}
//
//
//void IPerformFeatureAnalysis(char* data_folder)
//{
//	feature_analyser_.ReadFeatures_FromFiles(data_folder);
//	Thresholds threshold;
//	ThresholdingResult thresholding_result = feature_analyser_.ApplyThreshold(threshold);
//	scorer_.PerformAssessment(thresholding_result);
//}
//
//void ISaveAnalysisResult(char* result_folder)
//{
//	scorer_.SaveResultToHDD(result_folder);
//}
