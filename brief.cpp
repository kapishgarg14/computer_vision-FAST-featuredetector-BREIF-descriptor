#include<iostream>
#include<opencv2/opencv_modules.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<string>
#include<algorithm>
using namespace std;
using namespace cv;
using namespace xfeatures2d;
#include"FAST.CPP"
class BRIEF{
    public:
   vector<vector<int> > des;
   vector<KeyPoint> keypoint;
   Mat img;
   Mat img_gray;
   BRIEF(Mat src,vector<KeyPoint> kp){
   src.copyTo(img);
   cvtColor(img,img_gray,COLOR_BGR2GRAY);
   GaussianBlur(img_gray,img_gray,Size(5,5),2.0);
   keypoint=kp;
   }
   void compute(){
       Mat img2;
       img_gray.convertTo(img2,CV_32FC1);
       generate_descriptor(keypoint,des,img2);

   }
void descriptor_point(Mat img,vector<int>& des,int x,int y){
    RNG genx,geny;
     for(int i=0;i<32;i++){
         int sum=0;
         for(int j=0;j<8;j++){
             int x1=genx.uniform(x-25,x+25);
             int y1=geny.uniform(y-25,y+25);
             int x2=genx.uniform(x-25,x+25);
             int y2=geny.uniform(y-25,y+25);
             if(img.at<float>(y1,x1)>img.at<float>(y2,x2))
             sum+=pow(2,7-j);
             }
         des.push_back(sum);
     }
}
void generate_descriptor(vector<KeyPoint> kp,vector<vector<int> >& ds,Mat img_gray){
    for(int i=0;i<kp.size();i++){
        vector<int> d;
        descriptor_point(img_gray,d,kp[i].pt.x,kp[i].pt.y);
        ds.push_back(d);
    }
    
}
void get_descriptor(Mat &ds1){
    ds1=Mat(des.size(),des[0].size(),CV_32FC1);
    for(int i=0;i<des.size();i++){
        for(int j=0;j<des[0].size();j++)
        ds1.at<float>(i,j)=des[i][j];
    }
            ds1.convertTo(ds1,CV_8U);
}
};

bool f(DMatch d1,DMatch d2){
    return d2.distance>d1.distance;
}
int main(){
     Mat img=imread("input.jpg");
    Mat test=imread("n2.jpg");
     myFAST detector1(img,0.3);
     myFAST detector2(test,0.3);
     detector1.detect();
     detector2.detect();
     detector1.show_keypoints();
     detector2.show_keypoints();
      BRIEF ext1(img,detector1.kp);
    BRIEF ext2(test,detector2.kp);
    ext1.compute();
    ext2.compute();
      vector<DMatch> match;
      BFMatcher bf(NORM_HAMMING,true);
  
Mat ds1,ds2;
ext1.get_descriptor(ds1);ext2.get_descriptor(ds2);
    bf.match(ds1,ds2,match);
        sort(match.begin(),match.end(),f);
        match.erase(match.begin()+100,match.end());
        Mat out;
  drawMatches(img,detector1.kp,test,detector2.kp,match,out);
  namedWindow("matching");
  imshow("matching",out);
  waitKey(0);
  return 0;
}
