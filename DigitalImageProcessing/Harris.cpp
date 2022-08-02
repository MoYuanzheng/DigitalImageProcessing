#include"head.h"


Mat harris(Mat image) {
	image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1022(a)(building_original).tif", 0);

	//! 1. 计算一阶微分，分 x，y两个方向
	Mat gx, gy;
	cv::Scharr(image, gx, CV_64FC1, 1, 0, 3);
	cv::Scharr(image, gy, CV_64FC1, 0, 1, 3);


	//! 2. 求一阶偏微分平方及乘积
	Mat GxSquare(image.size(), CV_64FC1), GySquare(image.size(), CV_64FC1), GxGy(image.size(), CV_64FC1);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			GxSquare.at<double>(i, j) = gx.at<double>(i, j) * gx.at<double>(i, j);
			GySquare.at<double>(i, j) = gy.at<double>(i, j) * gy.at<double>(i, j);
			GxGy.at<double>(i, j) = gx.at<double>(i, j) * gy.at<double>(i, j);
		}
	}

	//! 3. 进行高斯加权
	Mat A(image.size(), CV_64FC1), C(image.size(), CV_64FC1), B(image.size(), CV_64FC1), detM(image.size(), CV_64FC1), traceM(image.size(), CV_64FC1), R(image.size(), CV_64FC1);
	Size ksize = { 3,3 };
	GaussianBlur(GxSquare, A, ksize, 1);
	GaussianBlur(GySquare, C, ksize, 1);
	GaussianBlur(GxGy, B, ksize, 1);

	//! 4. 计算响应值 R 
	double t = 0, alpha = 0.04, tempR = 0, max = 0;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			// AC - B^2
			detM.at<double>(i, j) = A.at<double>(i, j) * C.at<double>(i, j) - B.at<double>(i, j) * B.at<double>(i, j);

			// A + C
			traceM.at<double>(i, j) = A.at<double>(i, j) + C.at<double>(i, j);

			// 临时 R
			tempR = detM.at<double>(i, j) - alpha * traceM.at<double>(i, j) * traceM.at<double>(i, j);
			R.at<double>(i, j) = tempR;

		}
	}
	cv::minMaxLoc(R, NULL, &max, NULL, NULL);

	//! 5. 非极大值抑制 NMS 及 阈值过滤，保留像素即为灰度值
	int NMSsize = 3;
	copyMakeBorder(R, R, NMSsize / 2, NMSsize / 2, NMSsize / 2, NMSsize / 2, 0);
	for (int i = NMSsize / 2; i < R.rows - NMSsize / 2; i++) {
		for (int j = NMSsize / 2; j < R.cols - NMSsize / 2; j++) {
			if (R.at<double>(i, j) < 0.1 * max) {
				R.at<double>(i, j) = 0;
				continue;
			}
			for (int x = -NMSsize / 2; x <= NMSsize / 2; x++) {
				for (int y = -NMSsize / 2; y <= NMSsize / 2; y++) {
					if (R.at<double>(i, j) < R.at<double>(i + x, j + y)) {
						R.at<double>(i, j) = 0;
					}
				}
			}
		}
	}

	//! 6. 绘制到原图中
	Mat corner;
	image.copyTo(corner);
	cvtColor(corner, corner, COLOR_BGR2RGB);
	for (int i = NMSsize / 2; i < R.rows - NMSsize / 2; i++) {
		for (int j = NMSsize / 2; j < R.cols - NMSsize / 2; j++) {
			// AC - B^2
			if (R.at<double>(i, j) > 0) {
				cv::circle(corner, cv::Point(j - NMSsize / 2, i - NMSsize / 2), 8, cv::Scalar(0, 0, 255), 2);
			}
		}
	}

	imshow("corner", corner);
	waitKey(0);
}
