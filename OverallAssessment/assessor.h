#ifndef ASSESSOR_H_
#define ASSESSOR_H_

#include "feature_extractor.h"
#include "codewords.h"
#include <vector>

class Assessor
{
public:
	Assessor(){};
	~Assessor(){};
	void PerformAssessment();
	void Link_FeatureExtractor(FeatureExtractor &feature_extractor);

protected:
	FeatureExtractor *feature_extractor_;
	std::vector<bool> PerformThresholding_(const Codeword codeword, std::vector<float>& feature);
	std::vector<bool> SmoothBinaryArray_(std::vector<bool> &data, const float ratio);
};

#endif