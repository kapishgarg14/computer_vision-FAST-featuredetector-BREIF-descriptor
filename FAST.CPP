#include<iostream>
#include<opencv2/opencv_modules.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<string>
using namespace std;
using namespace cv;
using namespace xfeatures2d;
#include"FAST.h"
int main(){
    string s;cin>>s;
    Mat img=imread(s);
    float t;cin>>t;
   myFAST det(img,t);
	det.detect();
	det.show_keypoints();
  return 0;
}
