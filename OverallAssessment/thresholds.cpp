//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.07
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "thresholds.h"

std::pair<float, float> Thresholds::GetThresholds(Codeword codeword)
{
	const float MIN_FLOAT = -10000000;
	const float MAX_FLOAT = 10000000;
		
	switch (codeword)
	{
	case Codeword::Velocity_LeftHand_Low:
		return std::pair<float, float>(MIN_FLOAT, (float)10.0);
		break;
	case Codeword::Velocity_LeftHand_High:
		return std::pair<float, float>((float)60.0, MAX_FLOAT);
		break;
	case Codeword::Velocity_RightHand_Low:
		return std::pair<float, float>(MIN_FLOAT, (float)10.0);
		break;
	case Codeword::Velocity_RightHand_High:
		return std::pair<float, float>((float)60.0, MAX_FLOAT);
		break;
	case Codeword::Velocity_Global_Low:
		return std::pair<float, float>(MIN_FLOAT, (float)5.0);
		break;
	case Codeword::Velocity_Global_High:
		return std::pair<float, float>((float)30.0, MAX_FLOAT);
		break;
	case Codeword::Velocity_Foot_Low:
		return std::pair<float, float>(MIN_FLOAT, (float)2.0);
		break;
	case Codeword::Velocity_Foot_High:
		return std::pair<float, float>((float)10.0, MAX_FLOAT);
		break;
	case Codeword::Energy_Low:
		return std::pair<float, float>(MIN_FLOAT, (float)3000.0);
		break;
	case Codeword::Energy_High:
		return std::pair<float, float>((float)500000.0, MAX_FLOAT);
		break;
	case Codeword::Foot_Closed:
		return std::pair<float, float>(MIN_FLOAT, (float)0.5);
		break;
	case Codeword::Foot_Stretched:
		return std::pair<float, float>((float)1.1, MAX_FLOAT);
		break;
	case Codeword::Direction_Backward:
		return std::pair<float, float>(MIN_FLOAT, (float)-5.0);
		break;
	case Codeword::Direction_Forward:
		return std::pair<float, float>((float)5.0, MAX_FLOAT);
		break;
	case Codeword::Balance_Backward:
		return std::pair<float, float>(MIN_FLOAT, (float)100.0);
		break;
	case Codeword::Balance_Forward:
		return std::pair<float, float>((float)100.0, MAX_FLOAT);
		break;
	case Codeword::Balance_LeaningLeft:
		return std::pair<float, float>(MIN_FLOAT, (float)-50.0);
		break;
	case Codeword::Balance_LeaningRight:
		return std::pair<float, float>((float)50, MAX_FLOAT);
		break;	
	case Codeword::Stability_Stable:
		return std::pair<float, float>(MIN_FLOAT, (float)20);
		break;
	case Codeword::Stability_Unstable:
		return std::pair<float, float>((float)50, MAX_FLOAT);
		break;
	case Openness_Low:
		return std::pair<float, float>(MIN_FLOAT, (float)100);
		break;
	case Openness_High:
		return std::pair<float, float>((float)500, MAX_FLOAT);
		break;
	default:
		return std::pair<float, float>(MIN_FLOAT, MAX_FLOAT);
		break;
	}
}