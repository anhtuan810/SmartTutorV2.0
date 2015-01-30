#include "assess_energy.h"
#include "thresholds.h"
#include "codewords.h"

void Assess_Energy::PerformAssessment()
{
	bi_energy_low_ = PerformThresholding_(Codeword::Energy_Low, feature_extractor_->GetEnergy());
	bi_energy_high_ = PerformThresholding_(Codeword::Energy_High, feature_extractor_->GetEnergy());
}

std::vector<bool> Assess_Energy::GetBinary_EnergyLow()
{
	return bi_energy_low_;
}

std::vector<bool> Assess_Energy::GetBinary_EnergyHigh()
{
	return bi_energy_high_;
}

