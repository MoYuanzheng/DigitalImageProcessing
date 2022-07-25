//! 例题 10.4 带噪边缘的区域中的一阶导数和二阶导数的性质
//! 中心差分 1 阶导数 -> [f(x + 1) - f(x - 1)] / 2 
//! 中心差分 2 阶导数 -> f(x + 1) - 2f(x) + f(x - 1)
#include"head.h"

void edgeModel(Mat image) {
	image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1008(b)(ramp edge).tif", 0);


	//
	Mat fd, sd;
	double average = 0;
	double stdDev = 0;

	Mat imageNoisy = GaussNoisy(image, average, stdDev);
	imshow("原噪声图", imageNoisy);
	imwrite("D:\\image/output/tif/imageNoisy_0.tif", imageNoisy);

	fd = firstDerivative(imageNoisy);
	sd = secondDerivative(imageNoisy);
	//! 输出 double 类图，用于 matlab 计算
	imwrite("D:\\image/output/tif/fd_0.tif", fd);
	imwrite("D:\\image/output/tif/sd_0.tif", sd);


	Mat sd_8, fd_8;
	normalize(fd, fd_8, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	normalize(sd, sd_8, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("一阶导数TIF", fd);
	imshow("二阶导数TIF", sd);

	//! 输出 uchar 类图，用于观察及记录
	imwrite("D:\\image/output/png/fd_0.png", fd_8);
	imwrite("D:\\image/output/png/sd_0.png", sd_8);
	imshow("一阶导数PNG", fd_8);
	imshow("二阶导数PNG", sd_8);

	Mat imageNoisyNor;
	normalize(imageNoisy, imageNoisyNor, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imwrite("D:\\image/output/png/imageNoisy_0.png", imageNoisy);

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

	return fd;
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

	return sd;
}

Mat GaussNoisy(Mat& image, double average, double stdDev) {
	Mat img_output(image.size(), image.type());
	Mat noise(image.size(), image.type());

	RNG rng(time(NULL));
	rng.fill(noise, RNG::NORMAL, average, stdDev);

	cv::add(image, noise, img_output);
	return img_output;
}