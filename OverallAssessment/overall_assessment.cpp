//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.06
//	2015.01.30: Return smoothed binary values 
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "overall_assessment.h"
#include "system_configuration.h"

OverallAssessment::OverallAssessment()
{
	//assess_energy_ = Assess_Energy(*feature_extractor_);
	//assess_global_displacement_ = Assess_GlobalDisplacement(*feature_extractor_);
	//assess_hand_gestures_ = Assessor_HandGestures(*feature_extractor_);
	//assess_posture_ = Assess_Posture(*feature_extractor_);
}

OverallAssessment::OverallAssessment(FeatureExtractor &feature_extractor)
{
	feature_extractor_ = &feature_extractor;
}

OverallAssessment::~OverallAssessment(){}

//////////////////////////////////////////////////////////////////////////
#pragma region Getters for series of scores

std::vector<float> OverallAssessment::GetScoreSeries_HandGesture()
{
	return score_series_hand_gesture_;
}

std::vector<float> OverallAssessment::GetScoreSeries_GlobalMovement()
{
	return score_series_global_movement_;
}

std::vector<float> OverallAssessment::GetScoreSeries_Energy()
{
	return score_series_energy_;
}

std::vector<float> OverallAssessment::GetScoreSeries_Posture()
{
	return score_series_posture_;
}

std::vector<float> OverallAssessment::GetScoreSeries_Overall()
{
	return score_series_overall_;
}

std::vector<bool> OverallAssessment::GetBinarySeries_ByCodeword(Codeword codeword)
{
	switch (codeword)
	{
	case Velocity_LeftHand_Low:
		return assess_hand_gestures_.GetBinary_Velocity_LeftHand_Low();
		break;
	case Velocity_LeftHand_High:
		return assess_hand_gestures_.GetBinary_Velocity_LeftHand_High();
		break;
	case Velocity_RightHand_Low:
		return assess_hand_gestures_.GetBinary_Velocity_RightHand_Low();
		break;
	case Velocity_RightHand_High:
		return assess_hand_gestures_.GetBinary_Velocity_RightHand_High();
		break;
	case Velocity_Global_Low:
		return assess_global_displacement_.GetBinary_GlobalVelocity_Low();
		break;
	case Velocity_Global_High:
		return assess_global_displacement_.GetBinary_GlobalVelocity_High();
		break;
	case Velocity_Foot_Low:
		return assess_global_displacement_.GetBinary_FootVelocity_Low();
		break;
	case Velocity_Foot_High:
		return assess_global_displacement_.GetBinary_FootVelocity_High();
		break;
	case Energy_Low:
		return assess_energy_.GetBinary_EnergyLow();
		break;
	case Energy_High:
		return assess_energy_.GetBinary_EnergyHigh();
		break;
	case Direction_Backward:
		return assess_global_displacement_.GetBinary_Direction_Backward();
		break;
	case Direction_Forward:
		return assess_global_displacement_.GetBinary_Direction_Forward();
		break;
	case Foot_Stretched:
		return assess_posture_.GetBinary_Foot_Stretched();
		break;
	case Foot_Closed:
		return assess_posture_.GetBinary_Foot_Closed();
		break;
	case Balance_Backward:
		return assess_posture_.GetBinary_Balance_Backward();
		break;
	case Balance_Forward:
		return assess_posture_.GetBinary_Balance_Forward();
		break;
	case Balance_LeaningLeft:
		return assess_posture_.GetBinary_Balance_Left();
		break;
	case Balance_LeaningRight:
		return assess_posture_.GetBinary_Balance_Right();
		break;
	case Stability_Stable:
		return assess_posture_.GetBinary_Stability_Stable();
		break;
	case Stability_Unstable:
		return assess_posture_.GetBinary_Stability_Unstable();
		break;
	case Openness_Low:
		return assess_posture_.GetBinary_Openness_Low();
		break;
	case Openness_High:
		return assess_posture_.GetBinary_Openness_High();
		break;
	default:
		return assess_posture_.GetBinary_Openness_High();
		break;
	}
}

std::vector<bool> OverallAssessment::GetBinarySeries_ByCodeword_Smoothed(Codeword codeword)
{
	switch (codeword)
	{
	case Foot_Stretched:
		return assess_posture_.GetBinary_Foot_Stretched_Smoothed();
		break;
	case Foot_Closed:
		return assess_posture_.GetBinary_Foot_Closed_Smoothed();
		break;
	case Balance_Backward:
		return assess_posture_.GetBinary_Balance_Backward_Smoothed();
		break;
	case Balance_Forward:
		return assess_posture_.GetBinary_Balance_Forward_Smoothed();
		break;
	case Balance_LeaningLeft:
		return assess_posture_.GetBinary_Balance_Left_Smoothed();
		break;
	case Balance_LeaningRight:
		return assess_posture_.GetBinary_Balance_Right_Smoothed();
		break;
	case Openness_Low:
		return assess_posture_.GetBinary_Openness_Low_Smoothed();
		break;
	case Openness_High:
		return assess_posture_.GetBinary_Openness_High_Smoothed();
		break;
	default:
		return assess_posture_.GetBinary_Openness_High_Smoothed();
		break;
	}
}


#pragma endregion



//////////////////////////////////////////////////////////////////////////
#pragma region Perform thresholding and assessment for scores

void OverallAssessment::PerformAssessment()
{
	ThresholdAllFeatures_();
	ComputeAllScores_();
}

void OverallAssessment::ThresholdAllFeatures_()
{
	assess_energy_.Link_FeatureExtractor(*feature_extractor_);
	assess_global_displacement_.Link_FeatureExtractor(*feature_extractor_);
	assess_hand_gestures_.Link_FeatureExtractor(*feature_extractor_);
	assess_posture_.Link_FeatureExtractor(*feature_extractor_);

	assess_energy_.PerformAssessment();
	assess_global_displacement_.PerformAssessment();
	assess_hand_gestures_.PerformAssessment();
	assess_posture_.PerformAssessment();
}

void OverallAssessment::ComputeAllScores_()
{
	float score_posture = assess_posture_.GetScore();
	score_series_posture_.push_back(score_posture);
	CheckBufferSize_(score_series_posture_, ASSESSMENT_SCORE_BUFFER_SIZE);

	float score_energy = assess_energy_.GetScore();
	score_series_energy_.push_back(score_energy);
	CheckBufferSize_(score_series_energy_, ASSESSMENT_SCORE_BUFFER_SIZE);

	float score_global_displacement = assess_global_displacement_.GetSore();
	score_series_global_movement_.push_back(score_global_displacement); 
	CheckBufferSize_(score_series_global_movement_, ASSESSMENT_SCORE_BUFFER_SIZE);

	float score_hand_gestures = assess_hand_gestures_.GetScore();
	score_series_hand_gesture_.push_back(score_hand_gestures);
	CheckBufferSize_(score_series_hand_gesture_, ASSESSMENT_SCORE_BUFFER_SIZE);

	float score_overall = (score_posture + score_energy + score_global_displacement + score_hand_gestures) / 4;
	score_series_overall_.push_back(score_overall);
	CheckBufferSize_(score_series_overall_, ASSESSMENT_SCORE_BUFFER_SIZE);
}

void OverallAssessment::Reset()
{
	score_series_hand_gesture_.clear();
	score_series_global_movement_.clear();
	score_series_energy_.clear();
	score_series_posture_.clear();
	score_series_overall_.clear();
}

#pragma endregion




//////////////////////////////////////////////////////////////////////////
#pragma region Private functions

std::vector<bool> OverallAssessment::ThresholdOneFeature_(std::vector<float>& feature, Codeword codeword)
{
	std::pair<float, float> thresholds = Thresholds::GetThresholds(codeword);

	std::vector<bool> result;
	for (size_t i = 0; i < feature.size(); i++)
	{
		if (feature[i] >= thresholds.first && feature[i] <= thresholds.second)
			result.push_back(true);
		else
			result.push_back(false);
	}
	return result;
}

void OverallAssessment::SmoothOneBinary_(std::vector<bool>& binary_cw)
{
	const int NEIGHBOR_RANGE = 15;
	const float RATIO = 0.6;

	for (size_t i = 0; i < binary_cw.size(); i++)
	{
		int id_start = i - NEIGHBOR_RANGE;
		int id_stop = i + NEIGHBOR_RANGE;
		if (id_start < 0) id_start = 0;
		if (id_stop > binary_cw.size() - 1) id_stop = binary_cw.size() - 1;

		while (binary_cw[id_start] && id_start <= id_stop)
		{
			id_start++;
		}
		while (binary_cw[id_stop] && id_start <= id_stop)
		{
			id_stop--;
		}
		if (id_start == id_stop)
		{
			return;
		}

		int count_positive = 0;
		for (size_t i = id_start; i <= id_stop; i++)
		{
			if (binary_cw[i]) count_positive++;
		}
		if ((float)count_positive / (id_stop - id_start + 1) >= RATIO)
		{
			for (size_t i = id_start; i <= id_stop; i++)
			{
				binary_cw[i] = true;
			}
		}
	}
}


//void OverallAssessment::SmoothOneBinary_(std::vector<bool>& binary_cw)
//{
//	const int NEIGHBOR_RANGE = 15;
//	const float RATIO = 0.6;
//
//	std::vector<bool> result;
//	for (size_t i = 0; i < binary_cw.size(); i++)
//	{
//		result.push_back(false);
//	}
//
//	for (size_t i = 0; i < binary_cw.size(); i++)
//	{
//		int id_start = i - NEIGHBOR_RANGE;
//		int id_stop = i + NEIGHBOR_RANGE;
//		if (id_start < 0) id_start = 0;
//		if (id_stop > binary_cw.size() - 1) id_stop = binary_cw.size() - 1;
//
//		int count_positive = 0;
//		for (size_t i = id_start; i <= id_stop; i++)
//		{
//			if (binary_cw[i]) count_positive++;
//		}
//		if ((float)count_positive / (id_stop - id_start + 1) >= RATIO)
//		{
//			for (size_t i = id_start; i <= id_stop; i++)
//			{
//				result[i] = true;
//			}
//		}
//	}
//
//	binary_cw = result;
//}

float OverallAssessment::CountBinaryPositive_(std::vector<bool> binary)
{
	int count = 0;
	for (size_t i = 0; i < binary.size(); i++)
	{
		if (binary[i]) count++;
	}
	return (float)count / binary.size();
}

void OverallAssessment::CheckBufferSize_(std::vector<float>& buffer, int size)
{
	if (buffer.size() > size)
		buffer.erase(buffer.begin());
}



#pragma endregion







