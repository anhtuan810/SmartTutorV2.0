//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.07
//	2015.01.28: Add Stability, adjust posture features
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef OVERALL_ASSESSMENET_H_
#define OVERALL_ASSESSMENET_H_

#include <vector>
#include "thresholds.h"
#include "feature_extractor.h"
#include "assess_energy.h"
#include "assess_global_displacement.h"
#include "assess_posture.h"
#include "assess_hand_gestures.h"

class OverallAssessment
{
public:
	OverallAssessment();
	OverallAssessment(FeatureExtractor &feature_extractor);
	~OverallAssessment();

	void Reset();
	void PerformAssessment();

	std::vector<float> GetScoreSeries_HandGesture();
	std::vector<float> GetScoreSeries_GlobalMovement();
	std::vector<float> GetScoreSeries_Energy();
	std::vector<float> GetScoreSeries_Posture();
	std::vector<float> GetScoreSeries_Overall();
	std::vector<bool> GetBinarySeries_ByCodeword(Codeword codeword);
	std::vector<bool> GetBinarySeries_ByCodeword_Smoothed(Codeword codeword);
	
private:
	FeatureExtractor *feature_extractor_;
	Assess_Energy assess_energy_;
	Assess_GlobalDisplacement assess_global_displacement_;
	Assessor_HandGestures assess_hand_gestures_;
	Assess_Posture assess_posture_;

	//	Score based on percentage of codeword appearance
	//
	std::vector<float> score_series_hand_gesture_;
	std::vector<float> score_series_global_movement_;
	std::vector<float> score_series_energy_;
	std::vector<float> score_series_posture_;
	std::vector<float> score_series_overall_;

	//	Private functions
	//
	void ThresholdAllFeatures_();
	void ComputeAllScores_();
	std::vector<bool> ThresholdOneFeature_(std::vector<float>& feature, Codeword codeword);
	void SmoothOneBinary_(std::vector<bool>& binary_cw);
	float CountBinaryPositive_(std::vector<bool> binary);
	void CheckBufferSize_(std::vector<float>& buffer, int size);
};

#endif