#include "assess_global_displacement.h"

void Assess_GlobalDisplacement::PerformAssessment()
{
	bi_velocity_global_high_ = PerformThresholding_(Codeword::Velocity_Global_High, feature_extractor_->GetVelocity_Global());
	bi_velocity_global_low_ = PerformThresholding_(Codeword::Velocity_Global_Low, feature_extractor_->GetVelocity_Global());
	bi_velocity_foot_high_ = PerformThresholding_(Codeword::Velocity_Foot_High, feature_extractor_->GetVelocity_Foot());
	bi_velocity_foot_low_ = PerformThresholding_(Codeword::Velocity_Foot_Low, feature_extractor_->GetVelocity_Foot());
	bi_direction_forward_ = PerformThresholding_(Codeword::Direction_Forward, feature_extractor_->GetDirection_BackForth());
	bi_direction_backward_ = PerformThresholding_(Codeword::Direction_Backward, feature_extractor_->GetDirection_BackForth());
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

