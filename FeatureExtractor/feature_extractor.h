//
//  Smart Tutor v2.0
//	FeatureExtractor: Extract features from skeletons
//
//  Created: 2015.01.02
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef FEATURE_EXTRACTOR_H_
#define FEATURE_EXTRACTOR_H_

#define BUFFER_SIZE 100

#include "sensor_reader.h"
#include "geometry.h"
#include "post_processing.h"
#include <vector>
//
//  Smart Tutor v2.0
//	FeatureExtractor: Extract features from skeletons
//
//  Created: 2015.01.02
//	2015.01.06: Add one more feature: Direction back/forth
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//


class FeatureExtractor
{
public:
	FeatureExtractor();
	~FeatureExtractor();
	void ProcessNewSample(Sensor_Reader& sensor_reader);
	int GetActualBufferSize();
	std::vector<float> GetVelocity_LeftHand();
	std::vector<float> GetVelocity_RightHand();
	std::vector<float> GetVelocity_Global();
	std::vector<float> GetVelocity_Foot();
	std::vector<float> GetEnergy();
	std::vector<float> GetDirection_BackForth();
	std::vector<float> GetFootStretch();
	std::vector<float> GetBalanceBackForth();
	std::vector<float> GetBalanceLeftRight();

private:
	Geometry geometry_;
	Post_Processing post_processing_;

	std::vector<float> f_velocity_left_hand_;
	std::vector<float> f_velocity_right_hand_;	
	std::vector<float> f_velocity_global_;
	std::vector<float> f_velocity_foot_;
	std::vector<float> f_energy_;
	std::vector<float> f_direction_back_forth_;
	std::vector<float> f_balance_left_right_;
	std::vector<float> f_balance_back_forth_;
	std::vector<float> f_foot_stretch_;

	void GetF_HandVelocity_(Sample& sample_latest, Sample& sample_second);
	void GetF_GlobalVelocity_(Sample& sample_latest, Sample& sample_second);
	void GetF_FeetVelocity_(Sample& sample_latest, Sample& sample_second);
	void GetF_Energy_(Sample& sample_latest, Sample& sample_second);
	void GetF_Direction_BackForth_(Sample& sample_latest, Sample& sample_second);
	void GetF_FeetStretch_(Sample& sample_latest);
	void GetF_BalanceBackForth_(Sample& sample_latest);
	void GetF_BalanceLeftRight_(Sample& sample_latest);

	void CheckBufferSize_(std::vector<float>& buffer, int size);
	float GetJointDisplacement_(Sample& sample_latest, Sample& sample_second, nite::JointType joint);
};

#endif