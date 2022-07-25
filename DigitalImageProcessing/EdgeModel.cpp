//! 例题 10.4 带噪边缘的区域中的一阶导数和二阶导数的性质
//! 中心差分 1 阶导数 -> [f(x + 1) - f(x - 1)] / 2 
//! 中心差分 2 阶导数 -> f(x + 1) - 2f(x) + f(x - 1)
#include"head.h"

void edgeModel(Mat image) {
	image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1008(b)(ramp edge).tif", 0);
	imshow("原图", image);
	Mat fd = firstDerivative(image);
	Mat sd = secondDerivative(image);
	imshow("一阶导数", fd);
	imshow("二阶导数", sd);
	waitKey(0);
}

Mat firstDerivative(Mat& image) {
	Mat fd = Mat::zeros(image.rows, image.cols - 2, CV_64F);
	imshow("一阶导数init", fd);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			double fdN = ((double)image.at<uchar>(i, j + 1) - (double)image.at<uchar>(i, j - 1)) / 2;
			fd.at<double>(i, j - 1) = 100 * fdN;
		}
	}

	Mat fdUchar;
	fd.convertTo(fdUchar, CV_8UC1);
	//normalize(fd, fd, 0, 1, NORM_MINMAX, CV_64F, Mat());

	return fdUchar;
}

Mat secondDerivative(Mat& image) {
	Mat sd = Mat::zeros(image.rows, image.cols - 2, CV_64F);
	imshow("二阶导数init", sd);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 1; j < image.cols - 1; j++) {
			double fdN = ((double)image.at<uchar>(i, j + 1) + (double)image.at<uchar>(i, j - 1) - 2 * (double)image.at<uchar>(i, j)) / 2;
			sd.at<double>(i, j - 1) = 100 * fdN;
		}
	}
	Mat sdUchar;
	sd.convertTo(sdUchar, CV_8UC1);

	return sdUchar;
}
