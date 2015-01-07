//
//  Smart Tutor v2.0
//	List of thresholds applied for each codewords
//
//  Created: 2015.01.06
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef THRESHOLDS_H_
#define THRESHOLDS_H_

#include <utility>

//////////////////////////////////////////////////////////////////////////
static enum Codeword
{
	Velocity_LeftHand_Low,
	Velocity_LeftHand_High,

	Velocity_RightHand_Low,
	Velocity_RightHand_High,

	Velocity_Global_Low,
	Velocity_Global_High,

	Velocity_Foot_Low,
	Velocity_Foot_High,

	Energy_Low,
	Energy_High,

	Direction_Backward,
	Direction_Forward,

	Foot_Stretched,
	Foot_Closed,

	Balance_Backward,
	Balance_Forward,

	Balance_LeaningLeft,
	Balance_LeaningRight,
};


//////////////////////////////////////////////////////////////////////////
class Thresholds
{
public:
	static std::pair<float, float> GetThresholds(Codeword codeword);
};

#endif // !THRESHOLDS_H_