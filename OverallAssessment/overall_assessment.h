//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.06
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include <vector>
#include "thresholds.h"
#include "feature_extractor.h"

class OverallAssessment
{
public:
	OverallAssessment();
	~OverallAssessment();

	float GetScoreHandGesture();
	float GetScoreGlobalMovement();
	float GetScoreEnergy();
	float GetScoreDirection();
	float GetScorePosture();
	float GetScoreOverall();
	std::vector<bool> GetBinaryByCodeword(Codeword codeword);

	void PerformAssessment(FeatureExtractor& feature_extractor);
	
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
	float score_hand_gesture_;
	float score_global_movement_;
	float score_energy_;
	float score_direction_;
	float score_posture_;
	float score_overall_;

	//
	//	Private functions
	//
	void ThresholdAllFeatures_(FeatureExtractor& feature_extractor);
	void ComputeAllScores_();

	std::vector<bool> ThresholdOneFeature_(std::vector<float> feature, Codeword codeword);
	void SmoothOneBinary_(std::vector<bool>& binary_cw);
	float CountBinaryPositive_(std::vector<bool> binary);	
};

