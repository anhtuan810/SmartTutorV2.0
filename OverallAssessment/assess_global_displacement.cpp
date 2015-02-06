#include "assess_global_displacement.h"
#include "thresholds.h"

void Assess_GlobalDisplacement::PerformAssessment()
{
	bi_velocity_global_high_ = PerformThresholding_(Codeword::Velocity_Global_High, feature_extractor_->GetVelocity_Global());
	bi_velocity_global_low_ = PerformThresholding_(Codeword::Velocity_Global_Low, feature_extractor_->GetVelocity_Global());
	bi_velocity_foot_high_ = PerformThresholding_(Codeword::Velocity_Foot_High, feature_extractor_->GetVelocity_Foot());
	bi_velocity_foot_low_ = PerformThresholding_(Codeword::Velocity_Foot_Low, feature_extractor_->GetVelocity_Foot());
	bi_direction_forward_ = PerformThresholding_(Codeword::Direction_Forward, feature_extractor_->GetDirection_BackForth());
	bi_direction_backward_ = PerformThresholding_(Codeword::Direction_Backward, feature_extractor_->GetDirection_BackForth());
	Calculate_Global_Disp_Score_();
}

std::vector<bool> Assess_GlobalDisplacement::GetBinary_GlobalVelocity_High()
{
	return bi_velocity_global_high_;
}

std::vector<bool> Assess_GlobalDisplacement::GetBinary_GlobalVelocity_Low()
{
	return bi_velocity_global_low_;
}

std::vector<bool> Assess_GlobalDisplacement::GetBinary_Direction_Forward()
{
	return bi_direction_forward_;
}

std::vector<bool> Assess_GlobalDisplacement::GetBinary_Direction_Backward()
{
	return bi_direction_backward_;
}

std::vector<bool> Assess_GlobalDisplacement::GetBinary_FootVelocity_High()
{
	return bi_velocity_foot_high_;
}

std::vector<bool> Assess_GlobalDisplacement::GetBinary_FootVelocity_Low()
{
	return bi_velocity_foot_low_;
}

float Assess_GlobalDisplacement::GetSore()
{
	return global_disp_score_;
}

void Assess_GlobalDisplacement::Calculate_Global_Disp_Score_()
{
	// Global displacement includes: (1) Amount of Global Displacement, (2) Direction
	// Think about this category by imagining presenter as a single point in 3D space
	//
	
	// The golden line for amount of global disp
	//
	float golden_line_disp = (Thresholds::GetThresholds(Codeword::Velocity_Global_High).first + Thresholds::GetThresholds(Codeword::Velocity_Global_Low).second) / 2;

	//	Deviation and normalization
	//
	float deviation_disp = CalculateDeviation_From_Golden_Line_(feature_extractor_->GetVelocity_Global(), golden_line_disp);
	deviation_disp /= feature_extractor_->GetVelocity_Global().size() *
		(Thresholds::GetThresholds(Codeword::Velocity_Global_High).first - Thresholds::GetThresholds(Codeword::Velocity_Global_Low).second);

	// Final score
	float ratio_forward = (float)CountBinaryPositive_(bi_direction_forward_) / feature_extractor_->GetDirection_BackForth().size();
	float ratio_backward = (float)CountBinaryPositive_(bi_direction_backward_) / feature_extractor_->GetDirection_BackForth().size();
	global_disp_score_ = 9;
	global_disp_score_ -= deviation_disp;
	global_disp_score_ += ratio_forward;
	global_disp_score_ -= ratio_backward;
}

