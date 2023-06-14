#include <opencv2/features2d.hpp>

    FlannBasedMatcher ff;//暴力匹配的方式：BFMatcher bf;
    vector<vector<DMatch>>matches;
    Mat d1 = Mat(k1).reshape(1,k1.size());d1.convertTo(d1,CV_32F);
    Mat d2 = Mat(k2).reshape(1,k2.size());d2.convertTo(d2,CV_32F);
    fb.knnMatch(d1,d2,matches,1);//暴力匹配：bf.knnMatch(d1,d2,matches,1)

    
