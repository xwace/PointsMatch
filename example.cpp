#include <opencv2/features2d.hpp>

    FlannBasedMatcher ff;//暴力匹配的方式１：BFMatcher bf;
    vector<vector<DMatch>>matches;
    Mat d1 = Mat(k1).reshape(1,k1.size());d1.convertTo(d1,CV_32F);
    Mat d2 = Mat(k2).reshape(1,k2.size());d2.convertTo(d2,CV_32F);
    fb.knnMatch(d1,d2,matches,1);//暴力匹配：bf.knnMatch(d1,d2,matches,1)

//暴力匹配的用法２

    vector<Point2d>ct1{Point2d{0,0},Point2d{10,10},Point2d{20,0}};
    vector<Point2d>ct2{Point2d{0,20},Point2d{11,11},Point2d{20,20}};

    BFMatcher fb;
    vector<DMatch>dm;
    Mat c1 = Mat(ct1).reshape(1,ct1.size());
    c1.convertTo(c1,CV_32F);
    Mat c2 = Mat(ct2).reshape(1,ct2.size());
    c2.convertTo(c2,CV_32F);
    fb.match(c1,c2,dm);
    for(auto d:dm){
        cout<<d.trainIdx<<" "<<d.queryIdx<<endl;
    }

    
