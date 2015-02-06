//
//  Smart Tutor v2.0
//	Overall assessment, including analysing the extracted features and giving scores
//
//  Created: 2015.01.28
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "feature_extractor.h"
#include "assessor.h"

class Assess_Energy : public Assessor
{
public:
	Assess_Energy(){};
	~Assess_Energy(){};

	void PerformAssessment();
	float GetScore();
	std::vector<bool> GetBinary_EnergyLow();
	std::vector<bool> GetBinary_EnergyHigh();	

private:
	std::vector<bool> bi_energy_low_;
	std::vector<bool> bi_energy_high_;
	float energy_score_;
	void CalculateEnergyScore_();
};
