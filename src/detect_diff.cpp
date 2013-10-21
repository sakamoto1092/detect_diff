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

int main(int arvc, char ** argv) {
	Mat img1, img2, img;
	Mat diff, diff2;
	Mat a, b;

	img1 = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE);
	img2 = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
	img = imread(argv[2], CV_LOAD_IMAGE_COLOR);
	absdiff(img1, img2, diff);
	threshold(diff, diff, 100, 255, CV_THRESH_BINARY);
	erode(diff, a, cv::Mat(), cv::Point(-1, -1), 3);
	dilate(a, b, cv::Mat(), cv::Point(-1, -1), 3);

	cv::HOGDescriptor hog; //
	hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector()); //
	std::vector<cv::Rect> found; // 検出結果格納用vector

	hog.detectMultiScale(img, found, 0, cv::Size(8, 8), cv::Size(16, 16), 1.05,
			2); // パラメータ設定
	// 画像，検出結果，閾値（SVMのhyper-planeとの距離），
	// 探索窓の移動距離（Block移動距離の倍数），
	// 画像外にはみ出た対象を探すためのpadding，
	// 探索窓のスケール変化係数，グルーピング係数

	std::vector<cv::Rect>::const_iterator it = found.begin(); // 検出結果の矩形を画像に書き込む
	// std::cout << "found:" << found.size() << std::endl;
	for (; it != found.end(); ++it) {
		cv::Rect r = *it;
		cv::rectangle(img, r.tl(), r.br(), cv::Scalar(0, 255, 0), 3);
	}
	namedWindow("detect", CV_WINDOW_NORMAL | CV_WINDOW_KEEPRATIO);
	imshow("detect", img);
	diff.copyTo(diff2, a);
	waitKey(0);
	imwrite("detect.jpg", img);
	imwrite("diff.jpg", diff);

	return 0;
}
