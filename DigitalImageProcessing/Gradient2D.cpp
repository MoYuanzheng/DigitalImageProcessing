#include"head.h"

Mat Gradient2D(Mat& image) {
	//image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1016(a)(building_original).tif", CV_64F);
	Mat imageNor;
	normalize(image, imageNor, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("原图", imageNor);
	imwrite("D:\\image/output/png/image.png", image);

	//! 水平分量 Sobel 核
	double horizontalSobelArray[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };

	//! 垂直分量 Sobel 核
	double verticalSobelArray[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };

	//! |g(x)|
	Mat convHorizenNor;
	Mat convHorizen = _convolution4(image, horizontalSobelArray);
	normalize(convHorizen, convHorizenNor, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("水平卷积图", convHorizen);
	imshow("水平卷积归一图", convHorizenNor);

	//! |g(y)|
	Mat convVerticalNor;
	Mat convVertical = _convolution4(image, verticalSobelArray);
	normalize(convVertical, convVerticalNor, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("垂直卷积图", convVertical);
	imshow("垂直卷积归一图", convVerticalNor);

	//! |g(x)| + |g(y)|
	Mat gradImageNor, gradImage;
	cv::add(convVerticalNor, convHorizenNor, gradImageNor);
	cv::add(convVertical, convHorizen, gradImage);
	imshow("梯度图像", gradImage);

	//waitKey(0);
	return gradImage;
}

Mat _convolution4(Mat image, double sobel[][3]) {

	cout << sobel[2][2] << endl;

	int w = image.cols;
	int h = image.rows;
	Mat convImage(h, w, CV_64F);
	Mat imageEx;

	copyMakeBorder(image, imageEx, 1, 1, 1, 1, cv::BORDER_REFLECT_101);

	for (int i = 1; i < imageEx.rows - 1; i++) {
		for (int j = 1; j < imageEx.cols - 1; j++) {
			double sum = 0;
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					sum += ((double)imageEx.at<double>(i + m - 1, j + n - 1) * sobel[m][n]);

					//! canny调用时应选择 double 类型，main调用时使用 uchar
					//sum += ((double)imageEx.at<uchar>(i + m - 1, j + n - 1) * sobel[m][n]);

				}
			}
			if (sum < 0) {
				convImage.at<double>(i - 1, j - 1) = -sum;
			}
			else {
				convImage.at<double>(i - 1, j - 1) = sum;
			}
		}
	}
	return convImage;
}