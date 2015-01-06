//
//  Smart Tutor v2.0
//	FeatureExtractor: Extract features from skeletons
//
//  Created: 2015.01.06
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include "post_processing.h"

Post_Processing::Post_Processing(){}

Post_Processing::~Post_Processing(){}

std::vector<float> Post_Processing::RemoveOurlier(std::vector<float>& input)
{
	const int RANGE_NEIGHBOR = 5;
	const float RATIO_PEAK = 4;

	std::vector<float> output(input.size());
	for (size_t i = 0; i < input.size(); i++)
	{
		output[i] = input[i];
	}

	for (size_t i = 0; i < output.size(); i++)
	{
		float average = Average_SubList_(output, i - RANGE_NEIGHBOR, i + RANGE_NEIGHBOR);
		if (std::abs(output[i] / average) > RATIO_PEAK)
		{
			output[i] = average;
		}		
	}

	return output;
}

std::vector<float> Post_Processing::SmoothByAveraging(std::vector<float>& input)
{
	const int RANGE_NEIGHBOR = 3;

	std::vector<float> output(input.size());
	for (size_t i = 0; i < input.size(); i++)
	{
		output[i] = Average_SubList_(input, i - RANGE_NEIGHBOR, i + RANGE_NEIGHBOR);
	}

	return output;
}

float Post_Processing::Average_SubList_(std::vector<float> data, int id_from, int id_to)
{
	if (id_from < 0)
		id_from = 0;
	if (id_to > data.size() - 1)
		id_to = data.size() - 1;

	float sum = 0;
	for (size_t i = id_from; i < id_to; i++)
	{
		sum += data[i];
	}

	return sum / data.size();
}
