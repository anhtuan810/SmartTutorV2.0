#include "assess_hand_gestures.h"


void Assessor_HandGestures::PerformAssessment()
{
	bi_velocity_left_hand_high_ = PerformThresholding_(Codeword::Velocity_LeftHand_High, feature_extractor_->GetVelocity_LeftHand());
	bi_velocity_left_hand_low_ = PerformThresholding_(Codeword::Velocity_LeftHand_Low, feature_extractor_->GetVelocity_LeftHand());
	bi_velocity_right_hand_low_ = PerformThresholding_(Codeword::Velocity_RightHand_Low, feature_extractor_->GetVelocity_RightHand());
	bi_velocity_right_hand_high_ = PerformThresholding_(Codeword::Velocity_RightHand_High, feature_extractor_->GetVelocity_RightHand());
}

std::vector<bool> Assessor_HandGestures::GetBinary_Velocity_LeftHand_Low()
{
	return bi_velocity_left_hand_low_;
}

std::vector<bool> Assessor_HandGestures::GetBinary_Velocity_LeftHand_High()
{
	return bi_velocity_left_hand_high_;
}

std::vector<bool> Assessor_HandGestures::GetBinary_Velocity_RightHand_Low()
{
	return bi_velocity_right_hand_low_;
}

std::vector<bool> Assessor_HandGestures::GetBinary_Velocity_RightHand_High()
{
	return bi_velocity_right_hand_high_;
}
