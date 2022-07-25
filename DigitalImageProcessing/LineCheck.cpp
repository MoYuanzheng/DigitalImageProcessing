#include"head.h"

Mat lineCheck(Mat& image) {
	image = cv::imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1005(a)(wirebond_mask).tif", 0);

	//! 普通 Laplace 核
	double LaplaceArray[3][3] = { {1,1,1},{1,-8,1},{1,1,1} };

	//! 水平线检测 Laplace 核
	double horizontalLaplaceArray[3][3] = { {-1,-1,-1},{2,2,2},{-1,-1,-1} };

	//! +45°（主对角线）Laplace核
	double majorLaplaceArray[3][3] = { {2,-1,-1},{-1,2,-1},{-1,-1,2} };

	//! 垂直线检测 Laplace 核
	double verticalLaplaceArray[3][3] = { {-1,2,-1},{-1,2,-1},{-1,2,-1} };

	//! -45°（副对角线）Laplace核
	double secondaryLaplaceArray[3][3] = { {-1,-1,2},{-1,2,-1},{2,-1,-1} };

	Mat LaplaceTemplate(3, 3, CV_64F, LaplaceArray);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {

			//! 更换核心需要在此赋值
			LaplaceTemplate.at<double>(i, j) = LaplaceArray[i][j];
		}
	}
	imshow("temp", LaplaceTemplate);
	Mat conv(image.rows, image.cols, CV_64F);

	conv = _convolution3(image, LaplaceTemplate);
	imshow("卷积图", conv);

	Mat norConv;
	normalize(conv, norConv, 0, 1, NORM_MINMAX, CV_64F, Mat());
	imshow("归一卷积图", norConv);

	Mat bin = binarization(conv, 1000);
	imshow("筛选后", bin);
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
					sum += ((double)imageEx.at<uchar>(i + m - 1, j + n - 1) * image_temp.at<double>(m, n));
				}
			}
			//! 标准 Laplace 图
			convImage.at<double>(i - 1, j - 1) = sum;

			/*--------------------------------------------------*/
			//! 绝对值 Laplace 图
			//if (sum < 0) {
			//	convImage.at<double>(i - 1, j - 1) = -sum;
			//}
			//else {
			//	convImage.at<double>(i - 1, j - 1) = sum;
			//}
			/*--------------------------------------------------*/
			//! 正值 Laplace 图
			//if (sum > 0) {
			//	convImage.at<double>(i - 1, j - 1) = sum;
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
