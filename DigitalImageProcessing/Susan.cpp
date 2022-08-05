#include"head.h"

Mat susan(Mat image) {
	image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1036(a)(original_septagon).tif", 0);
	int usan[7][7] = {
		{0, 0, 1, 1, 1, 0, 0},
		{0, 1, 1, 1, 1, 1, 0},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{1, 1, 1, 1, 1, 1, 1},
		{0, 1, 1, 1, 1, 1, 0},
		{0, 0, 1, 1, 1, 0, 0}
	};
	Mat R(image.rows + 3, image.cols + 3, CV_64FC1);

	R = USAN(image, usan);
	imshow("R", R);

	Mat Rhalf;
	R.copyTo(Rhalf);
	//! 过滤最大值的一半
	double g = R.at<double>(0, 0) * 0.5;
	g = 18;

	for (int i = 3; i < Rhalf.rows - 3; i++) {
		for (int j = 3; j < Rhalf.cols - 3; j++) {
			if (Rhalf.at<double>(i, j) >= g) {
				Rhalf.at<double>(i, j) = 0;
			}
			else {
				Rhalf.at<double>(i, j) = g - Rhalf.at<double>(i, j);
			}
		}
	}
	//half.convertTo(half, CV_8UC3);
	imshow("Rhalf", Rhalf);

	Mat NMS(image.size(), CV_64FC1);


	//! 去除 EX
	for (int i = 3; i < Rhalf.rows - 3; i++) {
		for (int j = 3; j < Rhalf.cols - 3; j++) {
			NMS.at<double>(i - 3, j - 3) = Rhalf.at<double>(i, j);
		}
	}

	//! 极大值抑制
	int NMSsize = 3;
	copyMakeBorder(NMS, NMS, NMSsize / 2, NMSsize / 2, NMSsize / 2, NMSsize / 2, 0);

	for (int i = NMSsize / 2; i < NMS.rows - NMSsize / 2; i++) {
		for (int j = NMSsize / 2; j < NMS.cols - NMSsize / 2; j++) {
			for (int x = -NMSsize / 2; x <= NMSsize / 2; x++) {
				for (int y = -NMSsize / 2; y <= NMSsize / 2; y++) {
					if (x == 0 && y == 0) {
						continue;
					}
					if (NMS.at<double>(i, j) <= NMS.at<double>(i + x, j + y)) {
						NMS.at<double>(i, j) = 0;
					}
				}
			}
		}
	}
	imshow("NMS", NMS);

	//!  绘制到原图中
	Mat corner;
	image.copyTo(corner);
	cvtColor(corner, corner, COLOR_BGR2RGB);
	for (int i = NMSsize / 2; i < NMS.rows - NMSsize / 2; i++) {
		for (int j = NMSsize / 2; j < NMS.cols - NMSsize / 2; j++) {
			if (NMS.at<double>(i, j) > 0) {
				cv::circle(corner, cv::Point(j - NMSsize / 2, i - NMSsize / 2), 8, cv::Scalar(0, 0, 255), 2);
			}
		}
	}

	imshow("corner", corner);
	waitKey(0);
	return corner;
}

//! 优化响应值计算方式
//! fun (原图，模板) =>（sum(r0)）
Mat USAN(Mat image, int temp[][7]) {
	image.convertTo(image, CV_64FC1);
	double t = 25;
	Mat imageEx(image.rows, image.cols, CV_64FC1);
	copyMakeBorder(image, imageEx, 3, 3, 3, 3, BORDER_REFLECT101);
	Mat sumR = Mat::zeros(imageEx.rows, imageEx.cols, CV_64FC1);
	double sum = 0, max = 0;

	for (int i = 3; i < imageEx.rows - 3; i++) {
		for (int j = 3; j < imageEx.cols - 3; j++) {
			sum = 0;
			for (int x = -3; x <= 3; x++) {
				for (int y = -3; y <= 3; y++) {
					if (temp[x + 3][y + 3] == 1) {
						sum += exp(-pow(((imageEx.at<double>(i + x, j + y) - imageEx.at<double>(i, j)) / t), 6));
					}
				}
			}
			if (sum > max) {
				max = sum;
			}
			sumR.at<double>(i, j) = sum;
		}
	}
	//! 最大值存入 R 值矩阵 0 0 点
	sumR.at<double>(0, 0) = max;
	//! 返回的矩阵是源图像扩充了三圈后的
	return sumR;
}

//! 原始响应值计算方式
Mat USAN2(Mat image, int temp[][7]) {
	image.convertTo(image, CV_64FC1);
	double t = 2;
	Mat imageEx(image.rows, image.cols, CV_64FC1);
	copyMakeBorder(image, imageEx, 3, 3, 3, 3, BORDER_REFLECT101);
	Mat sumR = Mat::zeros(imageEx.rows, imageEx.cols, CV_64FC1);
	double sum = 0, max = 0;

	for (int i = 3; i < imageEx.rows - 3; i++) {
		for (int j = 3; j < imageEx.cols - 3; j++) {
			sum = 0;
			for (int x = -3; x <= 3; x++) {
				for (int y = -3; y <= 3; y++) {
					if (temp[x + 3][y + 3] == 1) {
						if (imageEx.at<double>(i + x, j + y) - imageEx.at<double>(i, j) <= t) {
							sum++;
						}
					}
				}
			}
			if (sum > max) {
				max = sum;
			}
			sumR.at<double>(i, j) = sum;
		}
	}
	//! 最大值存入 R 值矩阵 0 0 点
	sumR.at<double>(0, 0) = max;
	//! 返回的矩阵是源图像扩充了三圈后的
	return sumR;
}