#include"head.h"

Mat lineCheck(Mat& image) {
	image = cv::imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1005(a)(wirebond_mask).tif", 0);

	int sharpenLaplaceArray[3][3] = { {1,1,1},{1,0,1},{1,1,1} };

	Mat sharpenLaplaceTemplate(3, 3, CV_8UC1, sharpenLaplaceArray);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sharpenLaplaceTemplate.at<uchar>(i, j) = sharpenLaplaceArray[i][j];
		}
	}
	imshow("temp", sharpenLaplaceTemplate);
	Mat conv(image.rows, image.cols, CV_64F);
	conv = _convolution3(image, sharpenLaplaceTemplate);
	imshow("卷积图", conv);
	normalize(conv, conv, 0, 1, NORM_MINMAX, CV_64F, Mat());
	imshow("归一卷积图", conv);

	cv::waitKey(0);
	return image;
}

Mat _convolution3(Mat& image, Mat& image_temp) {
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

			//! 标准拉普拉斯图
			convImage.at<double>(i - 1, j - 1) = t;

			/*--------------------------------------------------*/
			//! 绝对值拉普拉斯图
			//if (t < 0) {
			//	convImage.at<double>(i - 1, j - 1) = -t;
			//}
			//else {
			//	convImage.at<double>(i - 1, j - 1) = t;
			//}
			//! 正值拉普拉斯图
			//if (t > 0) {
			//	convImage.at<double>(i - 1, j - 1) = t;
			//}
			//else {
			//	convImage.at<double>(i - 1, j - 1) = 0;
			//}
			/*--------------------------------------------------*/
		}
	}
	//cv::imshow("convImage", convImage);
	//cv::waitKey(0);
	return convImage;
}
