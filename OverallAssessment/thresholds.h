//
//  Smart Tutor v2.0
//	List of thresholds applied for each codewords
//
//  Created: 2015.01.06
//
//  Copyright (c) 2015 Anh Tuan Nguyen. All rights reserved.
//

#ifndef THRESHOLDS_H_
#define THRESHOLDS_H_

#include <utility>
#include <vector>
#include "codewords.h"

class Thresholds
{
public:
	static std::pair<float, float> GetThresholds(Codeword codeword);
};

#endif // !THRESHOLDS_H_