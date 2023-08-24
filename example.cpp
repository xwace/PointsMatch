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

    //kdtree的用法；注意！！！vector<Index*>只能存放指針對象，因爲禁用了拷贝构造；同时入参input不能被析构，否则出错
    vector<shared_ptr<cv::flann::Index>> trees(node_num+1);
    vector<cv::Mat>cont_pts_vec;
    for(int i =0;i<=node_num;i++){
        Mat c = Mat(Contours[i]).reshape(1,(int)Contours[i].size());
        c.convertTo(c,CV_32F);
        cont_pts_vec.emplace_back(c.clone());//发生move?
    }

    for(int i =0;i<=node_num;i++){

        cv::flann::KDTreeIndexParams indexParamsPtr(cont_pts_vec[i].cols);  // 设置数据维度 in_mat.cols
        auto kdtreePtr = make_shared<cv::flann::Index>(cont_pts_vec[i], indexParamsPtr);
        trees[i] = kdtreePtr;//无法存放禁用赋值的对象实例
    }

    vector<int>vecIndex(1);
    vector<float>vecDist(1);
    float minDis{FLT_MAX};
    for(int i =0;i<=node_num;i++){trees[i]->knnSearch(cont_pts_vec[j].row(idx), vecIndex, vecDist, 1);}

    //暴力匹配
    Mat c1 = Mat(Contours[i]).reshape(1,(int)Contours[i].size());
    c1.convertTo(c1,CV_32F);
    Mat c2 = Mat(Contours[j]).reshape(1,(int)Contours[j].size());
    c2.convertTo(c2,CV_32F);
    Mat dst,nidx;
    batchDistance(c1,c2,dst,CV_32F,nidx,NORM_L2, 1, Mat(), 0, true);
    auto it = min_element(dst.begin<float>(),dst.end<float>());
    

    
