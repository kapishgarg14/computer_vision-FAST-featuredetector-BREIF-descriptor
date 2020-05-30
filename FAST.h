#include<iostream>
#include<opencv2/opencv_modules.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<string>
using namespace std;
using namespace cv;
using namespace xfeatures2d;
class myFAST{
Mat img;
Mat img_gray;
public:
vector<KeyPoint> kp;
double t;
myFAST(Mat src,double a){
src.copyTo(img);
cvtColor(img,img_gray,COLOR_BGR2GRAY);
GaussianBlur(img_gray,img_gray,Size(3,3),2.0);
t=a;
}
void detect(){
    Mat img2;
    img_gray.convertTo(img2,CV_32FC1);
    fast_feature_locator(img2,img,kp,t);
}
void show_keypoints(){
for(int i=0;i<kp.size();i++){
     circle(img,kp[i].pt,4,Scalar(255,255,0));
}
  namedWindow("feature");
    imshow("feature",img);
   
    waitKey(0);
}
private:
bool checkPoint(int x1,int y1,int r,Mat img,float t){
    vector<float> intensity;
    int x,y,p;
	x=0;
	y=r;
	p=3-(2*r);
	while(x<=y)
	{
	intensity.push_back(img.at<float>(y1+y,x1+x));
	intensity.push_back(img.at<float>(y1+y,x1-x));
	intensity.push_back(img.at<float>(y1-y,x1+x));
	intensity.push_back(img.at<float>(y1-y,x1-x));
	intensity.push_back(img.at<float>(y1+x,x1+y));
	intensity.push_back(img.at<float>(y1-x,x1+y));
	intensity.push_back(img.at<float>(y1+x,x1-y));
    intensity.push_back(img.at<float>(y1-x,x1-y));
		x=x+1;
		if(p<0)
		{
			p=p+4*(x)+6;
		}
		else
		{
			p=p+4*(x-y)+10;
			y=y-1;
            }}
            bool ans=false;;
            int k1=0,k2=0;
            float comp=t*img.at<float>(y1,x1);
            float curr_intensity=img.at<float>(y1,x1);
            if(curr_intensity+comp<intensity[1]&&curr_intensity+comp<intensity[5]&&curr_intensity+comp<intensity[9]&&curr_intensity+comp<intensity[13])
            return true;
            else if(curr_intensity-comp>intensity[1]&&curr_intensity-comp>intensity[5]&&curr_intensity-comp>intensity[9]&&curr_intensity-comp>intensity[13])
            return true;
            else return false;
            /*
            for(int i=0;i<intensity.size();i++){
                   if(img.at<float>(y1,x1)+comp<intensity[i])
                   k1++;
                   else if(img.at<float>(y1,x1)-comp>intensity[i])
                   k2++;
                   }

                   return k1>12||k2>12;
            */

}
void fast_feature_locator(Mat img_gray,Mat img,vector<KeyPoint>& kp,float t){
for(int i=3;i<img_gray.rows-3;i++){
    bool a=false;
              for(int j=3;j<img_gray.cols-3;j++){
                  a=checkPoint(j,i,3,img_gray,t);
                  if(a){
                  KeyPoint k(Point(j,i),0);
                  kp.push_back(k);
                  j+=30;
                  }
              }
    }
  
}
};