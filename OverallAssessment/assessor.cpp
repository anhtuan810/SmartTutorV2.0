#include "assessor.h"
#include <utility>
#include "thresholds.h"

std::vector<bool> Assessor::PerformThresholding_(const Codeword codeword, std::vector<float> &feature)
{
	std::pair<float, float> thresholds = Thresholds::GetThresholds(codeword);
	std::vector<bool> result;
	for (size_t i = 0; i < feature.size(); i++)
	{
		if (feature[i] > thresholds.first && feature[i] < thresholds.second)
			result.push_back(true);
		else
			result.push_back(false);
	}
	return result;
}

void Assessor::Link_FeatureExtractor(FeatureExtractor &feature_extractor)
{
	feature_extractor_ = &feature_extractor;
}

std::vector<bool> Assessor::SmoothBinaryArray_(std::vector<bool> &data, const float ratio)
{
	std::vector<bool> result;
	for (size_t i = 0; i < data.size(); i++)
	{
		result.push_back(false);
	}

	const int kWindowSize_half = 25;
	for (size_t i = 0; i < data.size(); i++)
	{
		int id_start = i - kWindowSize_half;
		int id_stop = i + kWindowSize_half;
		if (id_start < 0) 
			id_start = 0;
		if (id_stop > data.size() - 1) 
			id_stop = data.size() - 1;

		// Reach the most recent positive point of 2 borders
		while (id_start < id_stop)
		{
			if (data[id_start] == true)
				break;
			id_start ++;
		}
		while (id_stop > id_start)
		{
			if (data[id_stop] == true)
				break;
			id_stop--;
		}

		if (id_start < id_stop)
		{
			// Count the number of positive points within the compacted window
			int count = 0;
			for (size_t k = id_start; k <= id_stop; k++)
			{
				if (data[k] == true)
					count++;
			}

			// Check if number of positive points in the window reach the ratio
			if ((float)count / (kWindowSize_half * 2) >= ratio)
			{
				// Set all the range to positive
				for (size_t k = id_start; k <= id_stop; k++)
				{
					result[k] = true;
				}
				// Will be automatically negative if not being set
			}
		}
	}
	return result;
}

float Assessor::CalculateDeviation_From_Golden_Line_(std::vector<float>& data, const float& golden_value)
{
	float deviate = 0;
	for (size_t i = 0; i < data.size(); i++)
	{
		deviate += std::abs(data[i] - golden_value);
	}
	return deviate;
}

float Assessor::CountBinaryPositive_(std::vector<bool> binary)
{
	int count = 0;
	for (size_t i = 0; i < binary.size(); i++)
	{
		if (binary[i]) count++;
	}
	return (float)count / binary.size();
}
