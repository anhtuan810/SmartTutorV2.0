//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.28
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "assessor.h"

class Assessor_HandGestures : public Assessor
{
public:
	Assessor_HandGestures(){};
	~Assessor_HandGestures(){};

	void PerformAssessment();
	std::vector<bool> GetBinary_Velocity_LeftHand_Low();
	std::vector<bool> GetBinary_Velocity_LeftHand_High();
	std::vector<bool> GetBinary_Velocity_RightHand_Low();
	std::vector<bool> GetBinary_Velocity_RightHand_High();

private:
	std::vector<bool> bi_velocity_left_hand_low_;
	std::vector<bool> bi_velocity_left_hand_high_;
	std::vector<bool> bi_velocity_right_hand_low_;
	std::vector<bool> bi_velocity_right_hand_high_;
};