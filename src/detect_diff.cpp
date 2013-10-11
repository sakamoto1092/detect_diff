#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include<opencv2/nonfree/nonfree.hpp>
#include<opencv2/nonfree/features2d.hpp>
#include <sstream>
#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <boost/program_options.hpp>
#define PANO_W 6000
#define PANO_H 3000
using namespace std;
using namespace cv;


int main(int arvc,char ** argv){
	Mat img1, img2;
	Mat diff,diff2;
	Mat a,b;

	img1 = imread(argv[1],CV_LOAD_IMAGE_GRAYSCALE);
	img2 = imread(argv[2],CV_LOAD_IMAGE_GRAYSCALE);

	absdiff(img1,img2,diff);
	threshold(diff,diff,100,255,CV_THRESH_BINARY);
	erode(diff,a,cv::Mat(), cv::Point(-1, -1),3);
	dilate(a,b,cv::Mat(), cv::Point(-1, -1),3);
	imshow("diff",diff);
	diff.copyTo(diff2,a);
	waitKey(0);
	imwrite("diff.jpg",diff);


	return 0;
}
