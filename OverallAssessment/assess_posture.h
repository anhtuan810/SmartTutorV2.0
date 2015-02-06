//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.28
//	2015.01.29: Only take into account the postural behavior that longer than 1.5 seconds
//	2015.02.05: Change the method for scoring, based on the Golden lines
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "assessor.h"

class Assess_Posture : public Assessor
{
public:
	Assess_Posture(){};
	~Assess_Posture(){};

	void PerformAssessment(); 
	float GetScore();

	std::vector<bool> GetBinary_Velocity_LeftHand_Low();
	std::vector<bool> GetBinary_Foot_Stretched();
	std::vector<bool> GetBinary_Foot_Closed();
	std::vector<bool> GetBinary_Balance_Backward();
	std::vector<bool> GetBinary_Balance_Forward();
	std::vector<bool> GetBinary_Balance_Left();
	std::vector<bool> GetBinary_Balance_Right();
	std::vector<bool> GetBinary_Stability_Stable();
	std::vector<bool> GetBinary_Stability_Unstable();
	std::vector<bool> GetBinary_Openness_Low();
	std::vector<bool> GetBinary_Openness_High();

	std::vector<bool> GetBinary_Foot_Stretched_Smoothed();
	std::vector<bool> GetBinary_Foot_Closed_Smoothed();
	std::vector<bool> GetBinary_Balance_Backward_Smoothed();
	std::vector<bool> GetBinary_Balance_Forward_Smoothed();
	std::vector<bool> GetBinary_Balance_Left_Smoothed();
	std::vector<bool> GetBinary_Balance_Right_Smoothed();
	std::vector<bool> GetBinary_Openness_Low_Smoothed();
	std::vector<bool> GetBinary_Openness_High_Smoothed();

private:
	float posture_score_;

	std::vector<bool> bi_foot_stretched_;
	std::vector<bool> bi_foot_closed_;
	std::vector<bool> bi_balance_backward_;
	std::vector<bool> bi_balance_forward_;
	std::vector<bool> bi_balance_left_;
	std::vector<bool> bi_balance_right_;
	std::vector<bool> bi_stability_stable_;
	std::vector<bool> bi_stability_unstable_;
	std::vector<bool> bi_openness_low_;
	std::vector<bool> bi_openness_high_;

	std::vector<bool> bi_foot_stretched_smoothed_;
	std::vector<bool> bi_foot_closed_smoothed_;
	std::vector<bool> bi_balance_backward_smoothed_;
	std::vector<bool> bi_balance_forward_smoothed_;
	std::vector<bool> bi_balance_left_smoothed_;
	std::vector<bool> bi_balance_right_smoothed_;
	std::vector<bool> bi_openness_low_smoothed_;
	std::vector<bool> bi_openness_high_smoothed_;

	
	void CalculatePostureScore_();
};