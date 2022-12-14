

/*
 * FeaturesEngineering.h
 *
 *  Created on: Jun 4, 2022
 *      Author: Islam Ahmed
 */

#include <vector>
#include <map>
#include <algorithm>
#include <math.h>
#include <functional>




using namespace std;



std::vector<float> GetMean(const std::vector<std::vector<float>>& data);
float GetMean(const std::vector<float>& data);

std::vector<float> GetStdDev(const std::vector<std::vector<float>>& data);
float GetStdDev(const std::vector<float>& data);



void RemoveOutliers(std::vector<std::vector<float>>& data)