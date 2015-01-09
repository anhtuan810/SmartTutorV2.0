//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.06
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "overall_assessment.h"
#include "system_configuration.h"

OverallAssessment::OverallAssessment(){}

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

#pragma endregion




//////////////////////////////////////////////////////////////////////////
#pragma region Perform thresholding and assessment for scores

void OverallAssessment::AssessOneFeatureSet(FeatureExtractor& feature_extractor)
{
	ThresholdAllFeatures_(feature_extractor);
	ComputeAllScores_();
}
void OverallAssessment::ThresholdAllFeatures_(FeatureExtractor& feature_extractor)
{
	//
	//	Perform threshold, receive a binary vector marks position of codewords
	//
	bi_velocity_left_hand_low = ThresholdOneFeature_(feature_extractor.GetVelocity_LeftHand(), Codeword::Velocity_LeftHand_Low);
	bi_velocity_left_hand_high = ThresholdOneFeature_(feature_extractor.GetVelocity_LeftHand(), Codeword::Velocity_LeftHand_High);
	bi_velocity_right_hand_low = ThresholdOneFeature_(feature_extractor.GetVelocity_RightHand(), Codeword::Velocity_RightHand_Low);
	bi_velocity_right_hand_high = ThresholdOneFeature_(feature_extractor.GetVelocity_RightHand(), Codeword::Velocity_RightHand_High);
	bi_velocity_global_low = ThresholdOneFeature_(feature_extractor.GetVelocity_Global(), Codeword::Velocity_Global_Low);
	bi_velocity_global_high = ThresholdOneFeature_(feature_extractor.GetVelocity_Global(), Codeword::Velocity_Global_High);
	bi_velocity_foot_low = ThresholdOneFeature_(feature_extractor.GetVelocity_Foot(), Codeword::Velocity_Foot_Low);
	bi_velocity_foot_high = ThresholdOneFeature_(feature_extractor.GetVelocity_Foot(), Codeword::Velocity_Foot_High);
	bi_energy_low = ThresholdOneFeature_(feature_extractor.GetEnergy(), Codeword::Energy_Low);
	bi_energy_high = ThresholdOneFeature_(feature_extractor.GetEnergy(), Codeword::Energy_High);
	bi_direction_backward = ThresholdOneFeature_(feature_extractor.GetDirection_BackForth(), Codeword::Direction_Backward);
	bi_direction_forward = ThresholdOneFeature_(feature_extractor.GetDirection_BackForth(), Codeword::Direction_Forward);
	bi_foot_stretched = ThresholdOneFeature_(feature_extractor.GetFootStretch(), Codeword::Foot_Stretched);
	bi_foot_closed = ThresholdOneFeature_(feature_extractor.GetFootStretch(), Codeword::Foot_Stretched);
	bi_balance_backward = ThresholdOneFeature_(feature_extractor.GetBalanceBackForth(), Codeword::Balance_Backward);
	bi_balance_forward = ThresholdOneFeature_(feature_extractor.GetBalanceBackForth(), Codeword::Balance_Forward);
	bi_balance_left = ThresholdOneFeature_(feature_extractor.GetBalanceLeftRight(), Codeword::Balance_LeaningLeft);
	bi_balance_right = ThresholdOneFeature_(feature_extractor.GetBalanceLeftRight(), Codeword::Balance_LeaningRight);

	//
	//	Smooth the appearance of codewords
	//
	//SmoothOneBinary_(bi_velocity_left_hand_low);
	//SmoothOneBinary_(bi_velocity_left_hand_high);
	//SmoothOneBinary_(bi_velocity_right_hand_low);
	//SmoothOneBinary_(bi_velocity_right_hand_high);
	//SmoothOneBinary_(bi_velocity_global_low);
	//SmoothOneBinary_(bi_velocity_global_high);
	//SmoothOneBinary_(bi_velocity_foot_low);
	//SmoothOneBinary_(bi_velocity_foot_high);
	//SmoothOneBinary_(bi_energy_low);
	//SmoothOneBinary_(bi_energy_high);
	//SmoothOneBinary_(bi_direction_backward);
	//SmoothOneBinary_(bi_direction_forward);
	//SmoothOneBinary_(bi_foot_stretched);
	//SmoothOneBinary_(bi_foot_closed);
	//SmoothOneBinary_(bi_balance_backward);
	//SmoothOneBinary_(bi_balance_forward);
	//SmoothOneBinary_(bi_balance_left);
	//SmoothOneBinary_(bi_balance_right);
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
	float ratio_velocity_left_hand_low = CountBinaryPositive_(bi_velocity_left_hand_low);
	float ratio_velocity_left_hand_high = CountBinaryPositive_(bi_velocity_left_hand_high);
	float ratio_velocity_right_hand_low = CountBinaryPositive_(bi_velocity_right_hand_low);
	float ratio_velocity_right_hand_high = CountBinaryPositive_(bi_velocity_right_hand_high);
	float ratio_velocity_global_low = CountBinaryPositive_(bi_velocity_global_low);
	float ratio_velocity_global_high = CountBinaryPositive_(bi_velocity_global_high);
	float ratio_velocity_foot_low = CountBinaryPositive_(bi_velocity_foot_low);
	float ratio_velocity_foot_high = CountBinaryPositive_(bi_velocity_foot_high);
	float ratio_energy_low = CountBinaryPositive_(bi_energy_low);
	float ratio_energy_high = CountBinaryPositive_(bi_energy_high);
	float ratio_direction_backward = CountBinaryPositive_(bi_direction_backward);
	float ratio_direction_forward = CountBinaryPositive_(bi_direction_forward);
	float ratio_foot_stretched = CountBinaryPositive_(bi_foot_stretched);
	float ratio_foot_closed = CountBinaryPositive_(bi_foot_closed);
	float ratio_balance_backward = CountBinaryPositive_(bi_balance_backward);
	float ratio_balance_forward = CountBinaryPositive_(bi_balance_forward);
	float ratio_balance_left = CountBinaryPositive_(bi_balance_left);
	float ratio_balance_right = CountBinaryPositive_(bi_balance_right);
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
std::vector<bool> OverallAssessment::GetBinarySeries_ByCodeword(Codeword codeword)
{
	switch (codeword)
	{
	case Velocity_LeftHand_Low:
		return bi_velocity_left_hand_low;
		break;
	case Velocity_LeftHand_High:
		return bi_velocity_left_hand_high;
		break;
	case Velocity_RightHand_Low:
		return bi_velocity_right_hand_low;
		break;
	case Velocity_RightHand_High:
		return bi_velocity_right_hand_high;
		break;
	case Velocity_Global_Low:
		return bi_velocity_global_low;
		break;
	case Velocity_Global_High:
		return bi_velocity_global_high;
		break;
	case Velocity_Foot_Low:
		return bi_velocity_foot_low;
		break;
	case Velocity_Foot_High:
		return bi_velocity_foot_high;
		break;
	case Energy_Low:
		return bi_energy_low;
		break;
	case Energy_High:
		return bi_energy_high;
		break;
	case Direction_Backward:
		return bi_direction_backward;
		break;
	case Direction_Forward:
		return bi_direction_forward;
		break;
	case Foot_Stretched:
		return bi_foot_stretched;
		break;
	case Foot_Closed:
		return bi_foot_closed;
		break;
	case Balance_Backward:
		return bi_balance_backward;
		break;
	case Balance_Forward:
		return bi_balance_forward;
		break;
	case Balance_LeaningLeft:
		return bi_balance_left;
		break;
	case Balance_LeaningRight:
		return bi_balance_right;
		break;
	default:
		return bi_balance_right;
		break;
	}
}
void OverallAssessment::CheckBufferSize_(std::vector<float>& buffer, int size)
{
	if (buffer.size() > size)
		buffer.erase(buffer.begin());
}

#pragma endregion







