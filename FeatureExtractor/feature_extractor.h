//
//  Smart Tutor v2.0
//	FeatureExtractor: Extract features from skeletons
//
//  Created: 2015.01.02
//	2015.01.06: Add one more feature: Direction back/forth
//	2015.01.27: Improvement
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_EXTRACTOR_H_
#define FEATURE_EXTRACTOR_H_

#include "sensor_reader.h"
#include "geometry.h"
#include "post_processing.h"
#include <vector>

class FeatureExtractor
{
public:
	FeatureExtractor(Sensor_Reader &sensor_reader);
	~FeatureExtractor();

	void Reset();
	void ProcessNewSample();
	int GetActualBufferSize();

	std::vector<float> GetVelocity_LeftHand();
	std::vector<float> GetVelocity_RightHand();
	std::vector<float> GetVelocity_Hands();
	std::vector<float> GetVelocity_Global();
	std::vector<float> GetVelocity_Foot();

	std::vector<float> GetEnergy();
	std::vector<float> GetImpulsiveness();
	std::vector<float> GetDirection_BackForth();

	std::vector<float> GetFootStretch();
	std::vector<float> GetBalanceBackForth();
	std::vector<float> GetBalanceLeftRight();
	std::vector<float> GetStability(); // Get stability right after get balance left/right and back/forth - Only process on the last frame
	std::vector<float> GetOpenness();

private:
	Geometry geometry_;
	Sensor_Reader *sensor_reader_;
	Post_Processing post_processing_;
	Sample latest_sample_;
	Sample second_sample_;

	std::vector<float> f_velocity_left_hand_;
	std::vector<float> f_velocity_right_hand_;	
	std::vector<float> f_velocity_hands_;
	std::vector<float> f_velocity_global_;
	std::vector<float> f_velocity_foot_;

	std::vector<float> f_energy_;
	std::vector<float> f_impulsiveness_;
	std::vector<float> f_direction_back_forth_;

	std::vector<float> f_balance_left_right_;
	std::vector<float> f_balance_back_forth_;
	std::vector<float> f_stability_;
	std::vector<float> f_foot_stretch_;
	std::vector<float> f_openness_;

	void GetF_HandVelocity_();
	void GetF_GlobalVelocity_();
	void GetF_FeetVelocity_();

	void GetF_Energy_();
	void GetF_Impulsiveness_();
	void GetF_Direction_BackForth_();

	void GetF_FeetStretch_();
	void GetF_BalanceBackForth_();
	void GetF_BalanceLeftRight_();
	void GetF_Stability_();
	void GetF_Openness_();
	
	void CheckBufferSize_(std::vector<float>& buffer, int size);
	float GetJointDisplacement_(nite::JointType joint);
	float GetJointDisplacement_Shifted_(nite::JointType joint, nite::JointType ref_joint);
};

#endif