//! 例题 10.2 && 10.3

#include"head.h"

Mat outlierCheck(Mat& image) {
	image = cv::imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1004(b)(turbine_blade_black_dot).tif", 0);

	//! 普通Laplace核
	int LaplaceArray[3][3] = { {1,1,1},{1,0,1},{1,1,1} };

	Mat sharpenLaplaceTemplate(3, 3, CV_8UC1, LaplaceArray);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sharpenLaplaceTemplate.at<uchar>(i, j) = LaplaceArray[i][j];
		}
	}
	imshow("temp", sharpenLaplaceTemplate);
	Mat conv(image.rows, image.cols, CV_8UC1);
	conv = _convolution2(image, sharpenLaplaceTemplate);
	normalize(conv, conv, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("卷积图", conv);
	Mat bin = binarization(conv, 1000.0);
	imshow("孤立点", bin);

	cv::waitKey(0);
	return image;
}

Mat _convolution2(Mat& image, Mat& image_temp) {
	int w = image.cols;
	int h = image.rows;
	Mat convImage(h, w, CV_64F);
	Mat imageEx;
	copyMakeBorder(image, imageEx, 1, 1, 1, 1, cv::BORDER_REFLECT_101);
	imshow("imageEx", imageEx);
	for (int i = 1; i < imageEx.rows - 1; i++) {
		for (int j = 1; j < imageEx.cols - 1; j++) {
			double sum = 0;
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					sum += (imageEx.at<uchar>(i + m - 1, j + n - 1) * image_temp.at<uchar>(m, n));
				}
			}
			double t = sum - 8 * imageEx.at<uchar>(i, j);

			if (t > 0) {
				convImage.at<double>(i - 1, j - 1) = t;
			}
			else {
				convImage.at<double>(i - 1, j - 1) = 0;
			}
		}
	}
	cv::imshow("convImage", convImage);
	//cv::waitKey(0);
	return convImage;
}

Mat binarization(Mat& image, double flag) {
	Mat bin;
	image.copyTo(bin);
	for (int i = 0; i < bin.rows; i++) {
		for (int j = 0; j < bin.cols; j++) {

			if (bin.at<double>(i, j) < flag) {
				bin.at<double>(i, j) = 0;
			}
		}
	}
	return bin;
}
