#include "assess_hand_gestures.h"
#include "thresholds.h"

void Assessor_HandGestures::PerformAssessment()
{
	bi_velocity_left_hand_high_ = PerformThresholding_(Codeword::Velocity_LeftHand_High, feature_extractor_->GetVelocity_LeftHand());
	bi_velocity_left_hand_low_ = PerformThresholding_(Codeword::Velocity_LeftHand_Low, feature_extractor_->GetVelocity_LeftHand());
	bi_velocity_right_hand_low_ = PerformThresholding_(Codeword::Velocity_RightHand_Low, feature_extractor_->GetVelocity_RightHand());
	bi_velocity_right_hand_high_ = PerformThresholding_(Codeword::Velocity_RightHand_High, feature_extractor_->GetVelocity_RightHand());

	Calculate_Score_Hand_Gestures();
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

float Assessor_HandGestures::GetScore()
{
	return score_hand_gestures_;
}

void Assessor_HandGestures::Calculate_Score_Hand_Gestures()
{
	// Golden lines
	//
	float golden_hands_velocity = Thresholds::GetThresholds(Codeword::Velocity_LeftHand_High).first + Thresholds::GetThresholds(Codeword::Velocity_LeftHand_Low).second;

	// Deviation and normalization
	//
	float deviation = CalculateDeviation_From_Golden_Line_(feature_extractor_->GetVelocity_Hands(), golden_hands_velocity);
	deviation /= feature_extractor_->GetVelocity_Hands().size() *
		(Thresholds::GetThresholds(Codeword::Velocity_LeftHand_High).first - Thresholds::GetThresholds(Codeword::Velocity_LeftHand_Low).second);

	// Score
	score_hand_gestures_ = 9;
	score_hand_gestures_ -= deviation;
}
