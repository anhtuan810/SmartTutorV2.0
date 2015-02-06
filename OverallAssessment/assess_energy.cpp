#include "assess_energy.h"
#include "thresholds.h"
#include "codewords.h"

void Assess_Energy::PerformAssessment()
{
	bi_energy_low_ = PerformThresholding_(Codeword::Energy_Low, feature_extractor_->GetEnergy());
	bi_energy_high_ = PerformThresholding_(Codeword::Energy_High, feature_extractor_->GetEnergy());
	CalculateEnergyScore_();
}

std::vector<bool> Assess_Energy::GetBinary_EnergyLow()
{
	return bi_energy_low_;
}

std::vector<bool> Assess_Energy::GetBinary_EnergyHigh()
{
	return bi_energy_high_;
}

float Assess_Energy::GetScore()
{
	return energy_score_;
}

void Assess_Energy::CalculateEnergyScore_()
{
	//	Calculate the golden lines
	float golden_line_energy = (Thresholds::GetThresholds(Codeword::Energy_High).first + Thresholds::GetThresholds(Codeword::Energy_Low).second) / 2;

	//	Get the deviation
	float deviation_energy = CalculateDeviation_From_Golden_Line_(feature_extractor_->GetEnergy(), golden_line_energy);

	//	Normalize
	deviation_energy /= feature_extractor_->GetEnergy().size() *
		(Thresholds::GetThresholds(Codeword::Energy_High).first - Thresholds::GetThresholds(Codeword::Energy_Low).second);

	//	Impulsive degree
	int count_impulse = 0;
	for (size_t i = 0; i < feature_extractor_->GetImpulsiveness().size(); i++)
	{
		if (feature_extractor_->GetImpulsiveness()[i] > 0)
			count_impulse++;
	}

	energy_score_ = 9;

	if (feature_extractor_->GetActualBufferSize() > 10)
	{
		energy_score_ -= deviation_energy * 2;
		energy_score_ += count_impulse / feature_extractor_->GetImpulsiveness().size();
		if (energy_score_ < 3) energy_score_ = 3;
		if (energy_score_ > 10) energy_score_ = 10;
	}
}

