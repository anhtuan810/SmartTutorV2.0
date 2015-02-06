//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.26
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_extractor.h"
#include "assessor.h"

class Assess_GlobalDisplacement : public Assessor
{
public:
	Assess_GlobalDisplacement(){};
	~Assess_GlobalDisplacement(){};

	std::vector<bool> GetBinary_GlobalVelocity_High();
	std::vector<bool> GetBinary_GlobalVelocity_Low();
	std::vector<bool> GetBinary_FootVelocity_High();
	std::vector<bool> GetBinary_FootVelocity_Low();
	std::vector<bool> GetBinary_Direction_Forward();
	std::vector<bool> GetBinary_Direction_Backward();
	void PerformAssessment();
	float GetSore();

private:
	std::vector<bool> bi_velocity_global_low_;
	std::vector<bool> bi_velocity_global_high_;
	std::vector<bool> bi_velocity_foot_low_;
	std::vector<bool> bi_velocity_foot_high_;
	std::vector<bool> bi_direction_backward_;
	std::vector<bool> bi_direction_forward_;

	float global_disp_score_;

	void Calculate_Global_Disp_Score_();
};