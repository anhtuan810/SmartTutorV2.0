//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.07
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef OVERALL_ASSESSMENET_H_
#define OVERALL_ASSESSMENET_H_

#include <vector>
#include "thresholds.h"
#include "feature_extractor.h"

class OverallAssessment
{
public:
	OverallAssessment();
	~OverallAssessment();

	std::vector<float> GetScoreSeries_HandGesture();
	std::vector<float> GetScoreSeries_GlobalMovement();
	std::vector<float> GetScoreSeries_Energy();
	std::vector<float> GetScoreSeries_Direction();
	std::vector<float> GetScoreSeries_Posture();
	std::vector<float> GetScoreSeries_Overall();
	std::vector<bool> GetBinarySeries_ByCodeword(Codeword codeword);

	void AssessOneFeatureSet(FeatureExtractor& feature_extractor);
	
private:
	//
	// List of thresholded features as binary array = appearance of codewords
	//
	std::vector<bool> bi_velocity_left_hand_low;
	std::vector<bool> bi_velocity_left_hand_high;
	std::vector<bool> bi_velocity_right_hand_low;
	std::vector<bool> bi_velocity_right_hand_high;
	std::vector<bool> bi_velocity_global_low;
	std::vector<bool> bi_velocity_global_high;
	std::vector<bool> bi_velocity_foot_low;
	std::vector<bool> bi_velocity_foot_high;
	std::vector<bool> bi_energy_low;
	std::vector<bool> bi_energy_high;
	std::vector<bool> bi_direction_backward;
	std::vector<bool> bi_direction_forward;
	std::vector<bool> bi_foot_stretched;
	std::vector<bool> bi_foot_closed;
	std::vector<bool> bi_balance_backward;
	std::vector<bool> bi_balance_forward;
	std::vector<bool> bi_balance_left;
	std::vector<bool> bi_balance_right;
	//
	//	Score based on percentage of codeword appearance
	//
	std::vector<float> score_series_hand_gesture_;
	std::vector<float> score_series_global_movement_;
	std::vector<float> score_series_energy_;
	std::vector<float> score_series_direction_;
	std::vector<float> score_series_posture_;
	std::vector<float> score_series_overall_;
	//
	//	Private functions
	//
	void ThresholdAllFeatures_(FeatureExtractor& feature_extractor);
	void ComputeAllScores_();
	std::vector<bool> ThresholdOneFeature_(std::vector<float>& feature, Codeword codeword);
	void SmoothOneBinary_(std::vector<bool>& binary_cw);
	float CountBinaryPositive_(std::vector<bool> binary);	
	void CheckBufferSize_(std::vector<float>& buffer, int size);
};

#endif