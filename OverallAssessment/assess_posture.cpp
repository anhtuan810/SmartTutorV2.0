#include "assess_posture.h"
#include "thresholds.h"

void Assess_Posture::PerformAssessment()
{
	bi_foot_stretched_ = PerformThresholding_(Codeword::Foot_Stretched, feature_extractor_->GetFootStretch());
	bi_foot_closed_ = PerformThresholding_(Codeword::Foot_Closed, feature_extractor_->GetFootStretch());
	bi_balance_backward_ = PerformThresholding_(Codeword::Balance_Backward, feature_extractor_->GetBalanceBackForth());
	bi_balance_forward_ = PerformThresholding_(Codeword::Balance_Forward, feature_extractor_->GetBalanceBackForth());
	bi_balance_left_ = PerformThresholding_(Codeword::Balance_LeaningLeft, feature_extractor_->GetBalanceLeftRight());
	bi_balance_right_ = PerformThresholding_(Codeword::Balance_LeaningRight, feature_extractor_->GetBalanceLeftRight());
	bi_stability_stable_ = PerformThresholding_(Codeword::Stability_Stable, feature_extractor_->GetStability());
	bi_stability_unstable_ = PerformThresholding_(Codeword::Stability_Unstable, feature_extractor_->GetStability());
	bi_openness_low_ = PerformThresholding_(Codeword::Openness_Low, feature_extractor_->GetOpenness());
	bi_openness_high_ = PerformThresholding_(Codeword::Openness_High, feature_extractor_->GetOpenness());

	bi_foot_closed_smoothed_ = SmoothBinaryArray_(bi_foot_closed_, 0.8);
	bi_foot_stretched_smoothed_ = SmoothBinaryArray_(bi_foot_stretched_, 0.8);
	bi_balance_backward_smoothed_ = SmoothBinaryArray_(bi_balance_backward_, 0.8);
	bi_balance_forward_smoothed_ = SmoothBinaryArray_(bi_balance_forward_, 0.8);
	bi_balance_left_smoothed_ = SmoothBinaryArray_(bi_balance_left_, 0.8);
	bi_balance_right_smoothed_ = SmoothBinaryArray_(bi_balance_right_, 0.8);
	bi_openness_low_smoothed_ = SmoothBinaryArray_(bi_openness_low_, 0.8);
	bi_openness_high_smoothed_ = SmoothBinaryArray_(bi_openness_high_, 0.8);

	CalculatePostureScore_();
}

std::vector<bool> Assess_Posture::GetBinary_Foot_Stretched()
{
	return bi_foot_stretched_;
}

std::vector<bool> Assess_Posture::GetBinary_Foot_Closed()
{
	return bi_foot_closed_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Backward()
{
	return bi_balance_backward_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Forward()
{
	return bi_balance_forward_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Left()
{
	return bi_balance_left_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Right()
{
	return bi_balance_right_;
}

std::vector<bool> Assess_Posture::GetBinary_Stability_Stable()
{
	return bi_stability_stable_;
}

std::vector<bool> Assess_Posture::GetBinary_Stability_Unstable()
{
	return bi_stability_unstable_;
}

std::vector<bool> Assess_Posture::GetBinary_Openness_Low()
{
	return bi_openness_low_;
}

std::vector<bool> Assess_Posture::GetBinary_Openness_High()
{
	return bi_openness_high_;
}

std::vector<bool> Assess_Posture::GetBinary_Foot_Stretched_Smoothed()
{
	return bi_foot_stretched_smoothed_;
}

std::vector<bool> Assess_Posture::GetBinary_Foot_Closed_Smoothed()
{
	return bi_foot_closed_smoothed_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Backward_Smoothed()
{
	return bi_balance_backward_smoothed_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Forward_Smoothed()
{
	return bi_balance_forward_smoothed_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Left_Smoothed()
{
	return bi_balance_left_smoothed_;
}

std::vector<bool> Assess_Posture::GetBinary_Balance_Right_Smoothed()
{
	return bi_balance_right_smoothed_;
}

std::vector<bool> Assess_Posture::GetBinary_Openness_Low_Smoothed()
{
	return bi_openness_low_smoothed_;
}

std::vector<bool> Assess_Posture::GetBinary_Openness_High_Smoothed()
{
	return bi_openness_high_smoothed_;
}

void Assess_Posture::CalculatePostureScore_()
{
	// Manually set the golden lines, as the middle line of the 2 thresholds
	//
	const float golden_foot_stretch = (Thresholds::GetThresholds(Codeword::Foot_Stretched).first + Thresholds::GetThresholds(Codeword::Foot_Closed).second) / 2;
	const float golden_balance_left_right = (Thresholds::GetThresholds(Codeword::Balance_LeaningRight).first + Thresholds::GetThresholds(Codeword::Balance_LeaningLeft).second) / 2;
	const float golden_balance_back_forth = (Thresholds::GetThresholds(Codeword::Balance_Forward).first + Thresholds::GetThresholds(Codeword::Balance_Backward).second) / 2;

	// Compute the deviation from the golden lines
	//
	float deviation_foot_stretch = CalculateDeviation_From_Golden_Line_(feature_extractor_->GetFootStretch(), golden_foot_stretch);
	float deviation_balance_left_right = CalculateDeviation_From_Golden_Line_(feature_extractor_->GetBalanceLeftRight(), golden_balance_left_right);
	float deviation_balance_back_forth = CalculateDeviation_From_Golden_Line_(feature_extractor_->GetBalanceBackForth(), golden_balance_back_forth);

	// Normalize the deviation by the range from low threshold to high threshold
	//
	deviation_foot_stretch /= feature_extractor_->GetFootStretch().size() * 
		(Thresholds::GetThresholds(Codeword::Foot_Stretched).first - Thresholds::GetThresholds(Codeword::Foot_Closed).second);
	deviation_balance_left_right /= feature_extractor_->GetBalanceLeftRight().size() *
		(Thresholds::GetThresholds(Codeword::Balance_LeaningRight).first - Thresholds::GetThresholds(Codeword::Balance_LeaningLeft).second);
	deviation_balance_back_forth /= feature_extractor_->GetBalanceBackForth().size() *
		(Thresholds::GetThresholds(Codeword::Balance_Forward).first - Thresholds::GetThresholds(Codeword::Balance_Backward).second);

	// Get postural score based on deviation from the golden lines
	//
	float ratio_stable = (float)CountBinaryPositive_(bi_stability_stable_) / feature_extractor_->GetStability().size();
	float ratio_unstable = (float)CountBinaryPositive_(bi_stability_unstable_) / feature_extractor_->GetStability().size();
	posture_score_ = 9;
	posture_score_ -= deviation_foot_stretch * 2;
	posture_score_ -= deviation_balance_left_right * 2;
	posture_score_ -= deviation_balance_back_forth * 1.5;
	posture_score_ -= ratio_unstable;
	posture_score_ += ratio_stable;
}

float Assess_Posture::GetScore()
{
	return posture_score_;
}

