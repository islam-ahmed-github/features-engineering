



/*
 * FeaturesEngineering.cpp
 *
 *  Created on: Jun 4, 2022
 *      Author: Islam Ahmed
 */
 




#include"FeaturesEngineering.h"




float CalcEuclideanDist(const std::vector<float>& f1, const std::vector<float>& f2 )
{
    if (f1.size() != f2.size()) return -1.0;
    double sum = 0.0, diff = 0.0;
    for (int c = 0; c < f1.size(); c++)
    {
        diff = f1[c] - f2[c];
        sum += (diff * diff);
    }
    return sqrt(sum);
}






std::vector<float> GetMean(const std::vector<std::vector<float>>& data)
{
    std::vector<float> ret = data[0];
    for_each(data.begin() + 1, data.end(), [&ret](const std::vector<float>v) {std::transform(ret.begin(), ret.end(), v.begin(), ret.begin(), plus<float>()); });
    std::transform(ret.begin(), ret.end(), ret.begin(), bind2nd(divides<float>(), (float)data.size()));
    return ret;
}




float GetMean(const std::vector<float>& data)
{
    float sum = data[0];
    for_each(data.begin() + 1, data.end(), [&sum](const float& v) {sum += v; });
    return sum / (float)data.size();
}




std::vector<float> GetStdDev(const std::vector<std::vector<float>>& data)
{
    
    std::vector<float> mean = GetMean(data);
    std::vector<float> ret;
    std::vector<float> temp(mean.size());

    auto x = [](const float& f1, const float& f2)->float { float dif = f1 - f2; return (dif * dif); };

    for (const auto i : data)
    {

        std::transform(i.begin(), i.end(), mean.begin(), temp.begin(), x);
        float sum = temp[0];
        for_each( temp.begin()+1, temp.end(), [&sum](const float& v) {sum += v; });
        ret.push_back(sqrt(sum/temp.size()));
    }

    return ret;

}




std::vector<float> GetStdDev(const std::vector<FaceImgFvec>& ImgFeatures)
{

    std::vector<std::vector<float>> data;
    data.reserve(ImgFeatures.size());
    for (int i = 0; i < ImgFeatures.size(); i++) data.push_back(ImgFeatures[i].ImgFvec);
    return GetStdDev(data);

}






float GetStdDev( const std::vector<float>& data )
{
    float mean = GetMean(data), sum=0.0;
    for_each(data.begin(), data.end(), [&sum,mean](const float& f) {float dif = f - mean; dif *= dif; sum += dif; });
    return sum/ (float)data.size();
}





void RemoveOutliers(std::vector<std::vector<float>>& data)
{

    if (data.size() < 3) return;

    std::vector<float> mean = GetMean(data);
    std::vector<float> temp(mean.size());
    float sum = 0;
    multimap<float, int> vs;


    auto x = [](const float& f1, const float& f2)->float { float dif = f1 - f2; return (dif * dif); };

    for (int i = 0; i < data.size(); ++i)
    {
        std::transform(data[i].begin(), data[i].end(), mean.begin(), temp.begin(), x);
        sum = temp[0];
        for_each(temp.begin() + 1, temp.end(), [&sum](const float& v) {sum += v; });
        vs.insert(std::pair<float, int>(sqrt(sum / temp.size()), i));
    }

    data.erase( data.begin() + vs.rbegin()->second );

}



