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

std::vector<float> OverallAssessment::GetScoreSeries_Direction()
{
	return score_series_direction_;
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
	//
	//	Single scores on each category
	//
	float score_hand_gesture = 10;
	float score_global_movement = 10;
	float score_energy = 10;
	float score_direction = 7;
	float score_posture = 0;
	float score_overall = 5;
	//
	//	Ratio of appearance of codewords
	//
	float ratio_velocity_left_hand_low = CountBinaryPositive_(assess_hand_gestures_.GetBinary_Velocity_LeftHand_Low());
	float ratio_velocity_left_hand_high = CountBinaryPositive_(assess_hand_gestures_.GetBinary_Velocity_LeftHand_High());
	float ratio_velocity_right_hand_low = CountBinaryPositive_(assess_hand_gestures_.GetBinary_Velocity_RightHand_Low());
	float ratio_velocity_right_hand_high = CountBinaryPositive_(assess_hand_gestures_.GetBinary_Velocity_RightHand_High());
	float ratio_velocity_global_low = CountBinaryPositive_(assess_global_displacement_.GetBinary_GlobalVelocity_Low());
	float ratio_velocity_global_high = CountBinaryPositive_(assess_global_displacement_.GetBinary_GlobalVelocity_High());
	float ratio_energy_low = CountBinaryPositive_(assess_energy_.GetBinary_EnergyLow());
	float ratio_energy_high = CountBinaryPositive_(assess_energy_.GetBinary_EnergyHigh());
	float ratio_direction_backward = CountBinaryPositive_(assess_global_displacement_.GetBinary_Direction_Backward());
	float ratio_direction_forward = CountBinaryPositive_(assess_global_displacement_.GetBinary_Direction_Forward());
	float ratio_foot_stretched = CountBinaryPositive_(assess_posture_.GetBinary_Foot_Stretched_Smoothed());
	float ratio_foot_closed = CountBinaryPositive_(assess_posture_.GetBinary_Foot_Closed_Smoothed());
	float ratio_balance_backward = CountBinaryPositive_(assess_posture_.GetBinary_Balance_Backward_Smoothed());
	float ratio_balance_forward = CountBinaryPositive_(assess_posture_.GetBinary_Balance_Forward_Smoothed());
	float ratio_balance_left = CountBinaryPositive_(assess_posture_.GetBinary_Balance_Left_Smoothed());
	float ratio_balance_right = CountBinaryPositive_(assess_posture_.GetBinary_Balance_Right_Smoothed());
	//
	//	Score simply based on ratio of codewords (positive and negative)
	//
	score_hand_gesture = score_hand_gesture
		- ratio_velocity_left_hand_low - ratio_velocity_right_hand_low
		- ratio_velocity_right_hand_low - ratio_velocity_right_hand_high;
	score_global_movement = score_global_movement
		- 2 * ratio_velocity_global_low - 2 * ratio_velocity_global_high;
	score_energy = score_energy
		- 2 * ratio_energy_low - 2 * ratio_energy_high;
	score_direction = score_direction
		+ ratio_direction_forward - ratio_direction_backward;
	score_posture = score_posture
		- ratio_foot_stretched - ratio_foot_closed
		- ratio_balance_backward + ratio_balance_forward
		- ratio_balance_left - ratio_balance_right;
	score_overall = (score_hand_gesture + score_global_movement + score_energy + score_direction + score_posture) / 5;
	//
	//	Push single scores to the score buffers
	//
	score_series_hand_gesture_.push_back(score_hand_gesture);
	score_series_global_movement_.push_back(score_global_movement);
	score_series_energy_.push_back(score_energy);
	score_series_direction_.push_back(score_direction);
	score_series_posture_.push_back(score_posture);
	score_series_overall_.push_back(score_overall);
	//
	// Check buffer size
	// 
	CheckBufferSize_(score_series_hand_gesture_, ASSESSMENT_SCORE_BUFFER_SIZE);
	CheckBufferSize_(score_series_global_movement_, ASSESSMENT_SCORE_BUFFER_SIZE);
	CheckBufferSize_(score_series_energy_, ASSESSMENT_SCORE_BUFFER_SIZE);
	CheckBufferSize_(score_series_direction_, ASSESSMENT_SCORE_BUFFER_SIZE);
	CheckBufferSize_(score_series_posture_, ASSESSMENT_SCORE_BUFFER_SIZE);
	CheckBufferSize_(score_series_overall_, ASSESSMENT_SCORE_BUFFER_SIZE);
}

void OverallAssessment::Reset()
{
	//bi_velocity_left_hand_low_.clear();
	//bi_velocity_left_hand_high_.clear();
	//bi_velocity_right_hand_low_.clear();
	//bi_velocity_right_hand_high_.clear();
	//bi_velocity_global_low_.clear();
	//bi_velocity_global_high_.clear();
	//bi_velocity_foot_low_.clear();
	//bi_velocity_foot_high_.clear();
	//bi_energy_low_.clear();
	//bi_energy_high_.clear();
	//bi_direction_backward_.clear();
	//bi_direction_forward_.clear();
	//bi_foot_stretched_.clear();
	//bi_foot_closed_.clear();
	//bi_balance_backward_.clear();
	//bi_balance_forward_.clear();
	//bi_balance_left_.clear();
	//bi_balance_right_.clear();

	score_series_hand_gesture_.clear();
	score_series_global_movement_.clear();
	score_series_energy_.clear();
	score_series_direction_.clear();
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







