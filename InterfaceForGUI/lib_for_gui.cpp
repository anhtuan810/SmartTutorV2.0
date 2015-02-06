//
//  Smart Tutor v2.0
//	Interface for GUI, create dynamic library to link from C++ to C#
//
//  Created: 2015.01.05
//	2015.01.21: Added the Feedback module
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#define HEIGHT 480
#define WIDTH 640

#include "lib_for_gui.h"
#include "sensor_reader.h"
#include "feature_extractor.h"
#include "overall_assessment.h"
#include "realtime_feedback.h"

Sensor_Reader sensor_reader;
FeatureExtractor feature_extractor(sensor_reader);
OverallAssessment overall_assessment(feature_extractor);
Realtime_Feedback realtime_feedback(sensor_reader, overall_assessment);

//////////////////////////////////////////////////////////////////////////
#pragma region Sensor Control

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
	feature_extractor.Reset();
	overall_assessment.Reset();
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

#pragma endregion


//////////////////////////////////////////////////////////////////////////
#pragma region Feature Exctractor

void IResetFeatureExtractor()
{
	feature_extractor.Reset();
}

void IExtractFeatureNewFrame()
{
	feature_extractor.ProcessNewSample();
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

float* IGetFeature_VelocityHands()
{
	std::vector<float> velocity = feature_extractor.GetVelocity_Hands();
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

float* IGetFeature_Impulsiveness()
{
	std::vector<float> impulsiveness = feature_extractor.GetImpulsiveness();
	return copy_vector(impulsiveness);
}

float* IGetFeature_DirectionBackForth()
{
	std::vector<float> direction = feature_extractor.GetDirection_BackForth();
	return copy_vector(direction);
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

float* IGetFeature_Stability()
{
	std::vector<float> stability = feature_extractor.GetStability();
	return copy_vector(stability);
}

float* IGetFeature_Openness()
{
	std::vector<float> openness = feature_extractor.GetOpenness();
	return copy_vector(openness);
}

#pragma endregion


//////////////////////////////////////////////////////////////////////////
#pragma region Overall Assessment, based on extracted features

void IAssessOneFeatureSet()
{
	overall_assessment.PerformAssessment();
}

int IGetActualScoreBufferSize()
{
	return overall_assessment.GetScoreSeries_Overall().size();
}

float* IGetScore_HandGesture()
{
	return copy_vector(overall_assessment.GetScoreSeries_HandGesture());
}

float* IGetScore_GlobalMovement()
{
	return copy_vector(overall_assessment.GetScoreSeries_GlobalMovement());
}

float* IGetScore_Energy()
{
	return copy_vector(overall_assessment.GetScoreSeries_Energy());
}

float* IGetScore_Posture()
{
	return copy_vector(overall_assessment.GetScoreSeries_Posture());
}

float* IGetScore_Overall()
{
	return copy_vector(overall_assessment.GetScoreSeries_Overall());
}

#pragma endregion


//////////////////////////////////////////////////////////////////////////
#pragma region Retrieve Binary of Codewords

bool* copy_vector(std::vector<bool> input)
{
	const int sz = input.size();
	bool* data = new bool[sz];
	for (size_t i = 0; i < sz; i++)
	{
		data[i] = input[i];
	}
	return data;
}

bool* IGetBinary_VelocityLeftHand_Low()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_LeftHand_Low));
}

bool* IGetBinary_VelocityLeftHand_High()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_LeftHand_High));
}

bool* IGetBinary_VelocityRightHand_Low()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_RightHand_Low));
}

bool* IGetBinary_VelocityRightHand_High()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_RightHand_High));
}

bool* IGetBinary_VelocityGlobal_Low()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_Global_Low));
}

bool* IGetBinary_VelocityGlobal_High()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_Global_High));
}

bool* IGetBinary_VelocityFoot_Low()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_Foot_Low));
}

bool* IGetBinary_VelocityFoot_High()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Velocity_Foot_High));
}

bool* IGetBinary_Energy_Low()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Energy_Low));
}

bool* IGetBinary_Energy_High()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Energy_High));
}

bool* IGetBinary_Direction_Backward()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Direction_Backward));
}

bool* IGetBinary_Direction_Forward()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Direction_Forward));
}

bool* IGetBinary_Foot_Stretched()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Foot_Stretched));
}

bool* IGetBinary_Foot_Closed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Foot_Closed));
}

bool* IGetBinary_Balance_Backward()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Balance_Backward));
}

bool* IGetBinary_Balance_Forward()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Balance_Forward));
}

bool* IGetBinary_Balance_Left()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Balance_LeaningLeft));
}

bool* IGetBinary_Balance_Right()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Balance_LeaningRight));
}

bool* IGetBinary_Stable()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Stability_Stable));
}

bool* IGetBinary_Unstable()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Stability_Unstable));
}

bool* IGetBinary_Openness_Low()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Openness_Low));
}

bool* IGetBinary_Openness_High()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword(Codeword::Openness_High));
}

//
// Smoothed binary data
//
bool* IGetBinary_Foot_Stretched_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Foot_Stretched));
}

bool* IGetBinary_Foot_Closed_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Foot_Closed));
}

bool* IGetBinary_Balance_Backward_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Balance_Backward));
}

bool* IGetBinary_Balance_Forward_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Balance_Forward));
}

bool* IGetBinary_Balance_Left_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Balance_LeaningLeft));
}

bool* IGetBinary_Balance_Right_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Balance_LeaningRight));
}

bool* IGetBinary_Openness_Low_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Openness_Low));
}

bool* IGetBinary_Openness_High_Smoothed()
{
	return copy_vector(overall_assessment.GetBinarySeries_ByCodeword_Smoothed(Codeword::Openness_High));
}
#pragma endregion


//////////////////////////////////////////////////////////////////////////
#pragma region The Feedback module

void IInitiateRealtimeFeedback()
{
	realtime_feedback.SetSensorReader(sensor_reader);
	realtime_feedback.SetOverallAssessment(overall_assessment);
}

char* IGetRealtimeFeedbackFrame()
{
	cv::Mat result = realtime_feedback.GetVisualisedFrame();
	char* data = new char[HEIGHT * WIDTH * 3];
	std::memcpy(data, result.data, WIDTH * HEIGHT * 3);
	return data;
}

int IGetNumberOfErrorPoints()
{
	return realtime_feedback.GetPoints_to_Annotate().size();
}

float* IGetErrorPoints(int index)
{
	nite::Point3f point = realtime_feedback.GetPoints_to_Annotate()[index];
	float x, y;
	Sample sample = sensor_reader.GetLatestSample();
	sensor_reader.ConvertJointCoordinateToDepth(sample.GetSkeleton(), nite::JOINT_HEAD, &x, &y);
	float *result = new float[2]{x, y};
	return result;
}

#pragma endregion
