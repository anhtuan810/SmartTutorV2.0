//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.28
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef CODEWORD_H_
#define CODEWORD_H_

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

	Stability_Stable,
	Stability_Unstable,

	Openness_Low,
	Openness_High
};

#endif