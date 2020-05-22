#include<iostream>
#include<opencv2/opencv_modules.hpp>
#include<opencv2/opencv.hpp>
#include<opencv2/xfeatures2d.hpp>
#include<opencv2/xfeatures2d/nonfree.hpp>
#include<string>
using namespace std;
using namespace cv;
using namespace xfeatures2d;
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
            for(int i=0;i<intensity.size();i++){
                   if(img.at<float>(y1,x1)+comp<intensity[i])
                   k1++;
                   else if(img.at<float>(y1,x1)-comp>intensity[i])
                   k2++;
                   }
                   return k1>12||k2>12;

}
void fast_feature_locator(Mat img_gray,Mat img,vector<Point>& kp,float t){
for(int i=3;i<img_gray.rows-3;i++){
    bool a=false;
              for(int j=3;j<img_gray.cols-3;j++){
                  a=checkPoint(j,i,3,img_gray,t);
                  if(a){
                  circle(img,Point(j,i),4,Scalar(0,255,0));
                  kp.push_back(Point(j,i));
                      j+=10;
                  }
              }
    }
    namedWindow("feature");
    imshow("feature",img);
   
    waitKey(0);
}
int main(){
    string s;cin>>s;
    Mat img=imread(s);
    float t;cin>>t;
    Mat img2,img_gray;
    vector<Point> kp;
    cvtColor(img,img2,COLOR_BGR2GRAY);
    img2.convertTo(img_gray,CV_32FC1);
   fast_feature_locator(img_gray,img,kp,t); 
  return 0;
}