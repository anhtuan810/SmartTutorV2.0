#include "assess_posture.h"

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

