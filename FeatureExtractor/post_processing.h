//
//  Smart Tutor v2.0
//	FeatureExtractor: Extract features from skeletons
//	Post process the extracted features
//
//  Created: 2015.01.06
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#include <vector>

class Post_Processing
{
public:
	Post_Processing();
	~Post_Processing();

	// Eliminate unwanted, error outliers by comparing with its neighbors
	std::vector<float> RemoveOurlier(std::vector<float>& input);
	std::vector<float> SmoothByAveraging(std::vector<float>& input);

private:
	// Average of one subset of list
	float Average_SubList_(std::vector<float> data, int id_from, int id_to);
};

