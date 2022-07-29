#include"head.h"
#define PI acos(-1)
void canny(Mat image) {
	//image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1022(a)(building_original).tif", 0);
	image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1026(a)(headCT-Vandy).tif", 0);

	//!? -------------------O P E N  C V-------------------------------
	{
		//	Mat OpenCV_Canny;
		//	//! OpenCV 
		//	cv::Canny(image, OpenCV_Canny, 400, 400, 3);


		//	imshow("OpenCV_Canny", OpenCV_Canny);


		//	//! 高斯模糊
		//	Mat OpenCV_Gaussian;
		//	cv::GaussianBlur(image, OpenCV_Gaussian, cv::Size(25, 25), 4, 4);
		//	//! 一阶导数
		//	Mat OpenCV_Gx, OpenCV_Gy;
		//	cv::Scharr(image, OpenCV_Gx, CV_64FC1, 1, 0, 3);
		//	cv::Scharr(image, OpenCV_Gy, CV_64FC1, 0, 1, 3);

		//	//! 梯度图S
		//	Mat magImg, angleImg_orig;
		//	cartToPolar(OpenCV_Gx, OpenCV_Gy, magImg, angleImg_orig, true);


		//	//! NMS	

		//	Mat OpenCV_NMS = AlphaDetermine(OpenCV_Gx, OpenCV_Gy);
		//	//normalize(gradValueNMS, gradValueNMS, 0, 1, NORM_MINMAX);
		//	imshow("极大抑制图", OpenCV_NMS);



		//	//! 双阈值过滤
		//	double maxValue_1 = MaxValue(magImg);

		//	Mat Canny_1 = ThresholdFilter(OpenCV_NMS, maxValue_1 * 0.1, maxValue_1 * 0.04);
		//	normalize(Canny_1, Canny_1, 0, 1, NORM_MINMAX);
		//	imshow("Canny_1", Canny_1);
		//
	}
	//!? -------------------O P E N  C V-------------------------------

	//! 求取高斯核
	Mat guassianKernel = GuassianKernel(2);

	//! 高斯卷积
	Mat conv = _convolution5(image, guassianKernel);
	Mat convNor;
	normalize(conv, convNor, 0, 1, NORM_MINMAX);
	imshow("高斯模糊", convNor);

	//! 求取梯度图幅度与方向
	Mat gradValue = GradientValue(conv);
	Mat gradAlpha = GradientAlpha(conv);
	Mat gradValueNor, gradAlphaNor;
	normalize(gradValue, gradValueNor, 0, 1, NORM_MINMAX);
	normalize(gradAlpha, gradAlphaNor, 0, 1, NORM_MINMAX);
	imshow("gradValueNor", gradValueNor);
	imshow("gradAlphaNor", gradAlphaNor);

	double maxValue = MaxValue(gradValue);
	cout << "maxValue = " << maxValue << endl;

	//! 判断角度并抑制非极大值
	Mat gradValueNMS = AlphaDetermine(gradValue, gradAlpha);
	normalize(gradValueNMS, gradValueNMS, 0, 1, NORM_MINMAX);
	imshow("极大抑制图", gradValueNMS);

	double TH = 0.3 * maxValue;
	double TL = 0.15 * maxValue;

	Mat canny = ThresholdFilter(gradValueNMS, TH, TL);
	normalize(canny, canny, 0, 1, NORM_MINMAX);
	imshow("C A N N Y", canny);
	waitKey(0);
}


//! 生成高斯核
Mat GuassianKernel(double sigma) {
	int n = 6 * sigma + 1;
	int size = (n - 1) / 2;
	Mat kernel = Mat::zeros(n, n, CV_64FC1);

	for (int i = -size; i <= size; i++) {
		for (int j = -size; j <= size; j++) {
			kernel.at<double>(i + size, j + size) = exp(-((i * i + j * j) / (2 * sigma * sigma)));
		}
	}
	imshow("guassion", kernel);
	return kernel;
}

//! 高斯卷积
Mat _convolution5(Mat image, Mat kernel) {
	Mat conv = Mat::zeros(image.size(), CV_64FC1);

	int size = (kernel.cols - 1) / 2;

	copyMakeBorder(image, image, size, size, size, size, BORDER_REFLECT101);

	for (int i = size; i < image.rows - size; i++) {
		for (int j = size; j < image.cols - size; j++) {
			double sum = 0;
			for (int x = 0; x < kernel.rows; x++) {
				for (int y = 0; y < kernel.cols; y++) {
					sum += (double)image.at<uchar>(i - size + x, j - size + y) * kernel.at<double>(x, y);
				}
			}
			conv.at<double>(i - size, j - size) = sum;
		}
	}

	return conv;
}

//! 求取梯度图 幅值
Mat GradientValue(Mat image) {
	double horizontalSobelArray[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	double verticalSobelArray[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };

	Mat convHorizen = _convolution6(image, horizontalSobelArray);
	Mat convVertical = _convolution6(image, verticalSobelArray);


	Mat gradValue = Mat::zeros(convHorizen.rows, convHorizen.cols, CV_64FC1);
	for (int i = 0; i < convHorizen.rows; i++) {
		for (int j = 0; j < convHorizen.cols; j++) {
			gradValue.at<double>(i, j) = sqrt(pow(convVertical.at<double>(i, j), 2) + pow(convHorizen.at<double>(i, j), 2));
		}
	}
	//Mat magImg, angleImg_orig;

	//? 自行计算的角度只有 -90° ~ 90°，arctan(x)的值域只有这些，不清楚是如何做的到 -PI~PI的
	//cartToPolar(convHorizen, convVertical, magImg, angleImg_orig, true);
	return gradValue;
}

//! 求取梯度图 角度
Mat GradientAlpha(Mat image) {

	double horizontalSobelArray[3][3] = { {-1,-2,-1},{0,0,0},{1,2,1} };
	double verticalSobelArray[3][3] = { {-1,0,1},{-2,0,2},{-1,0,1} };

	Mat convHorizen = _convolution6(image, horizontalSobelArray);
	//imshow("水平一阶导数", convHorizen);
	Mat convVertical = _convolution6(image, verticalSobelArray);
	//imshow("垂直一阶导", convVertical);

	Mat gradAlpha = Mat::zeros(convHorizen.rows, convHorizen.cols, CV_64FC1);
	for (int i = 0; i < convHorizen.rows; i++) {
		for (int j = 0; j < convHorizen.cols; j++) {
			gradAlpha.at<double>(i, j) = atan(convVertical.at<double>(i, j) / convHorizen.at<double>(i, j)) * 360 / PI;
		}
	}

	Mat magImg, angleImg_orig;

	//? 自行计算的角度只有 -90° ~ 90°，arctan(x)的值域只有这些，不清楚是如何做的到 -PI~PI的
	cartToPolar(convHorizen, convVertical, magImg, angleImg_orig, true);
	//imshow("梯度角度", angleImg_orig);
	//imshow("magImg", magImg);
	return angleImg_orig;
}

//! sobel 求一阶偏导
Mat _convolution6(Mat image, double sobel[][3]) {

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
				}
			}
			//convImage.at<double>(i - 1, j - 1) = sum;
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

//! 判别角度后进行非极大值抑制
Mat AlphaDetermine(Mat gradValue, Mat gradAlpha) {

	Mat gradValueNMS;
	gradValue.copyTo(gradValueNMS);

	for (int i = 1; i < gradAlpha.rows - 1; i++) {
		for (int j = 1; j < gradAlpha.cols - 1; j++) {
			if ((gradAlpha.at<double>(i, j) >= -22.5 && gradAlpha.at<double>(i, j) < 22.5) ||
				(gradAlpha.at<double>(i, j) < -157.5 || gradAlpha.at<double>(i, j) >= 157.5)) {
				//correctionAlpha.at<double>(i, j) = 1;
				if ((gradValue.at<double>(i + 1, j) > gradValue.at<double>(i, j)) ||
					(gradValue.at<double>(i - 1, j) > gradValue.at<double>(i, j))) {
					gradValueNMS.at<double>(i, j) = 0;
				}
			}
			if ((gradAlpha.at<double>(i, j) < -22.5 && gradAlpha.at<double>(i, j) >= -67.5) ||
				(gradAlpha.at<double>(i, j) >= 112.5 && gradAlpha.at<double>(i, j) < 157.5)) {
				//correctionAlpha.at<double>(i, j) = 2;
				if ((gradValue.at<double>(i + 1, j - 1) > gradValue.at<double>(i, j)) ||
					(gradValue.at<double>(i - 1, j + 1) > gradValue.at<double>(i, j))) {
					gradValueNMS.at<double>(i, j) = 0;
				}
			}
			if ((gradAlpha.at<double>(i, j) < -67.5 && gradAlpha.at<double>(i, j) >= -112.5) ||
				(gradAlpha.at<double>(i, j) >= 67.5 && gradAlpha.at<double>(i, j) < 112.5)) {
				//correctionAlpha.at<double>(i, j) = 3;
				if ((gradValue.at<double>(i, j + 1) > gradValue.at<double>(i, j)) ||
					(gradValue.at<double>(i, j - 1) > gradValue.at<double>(i, j))) {
					gradValueNMS.at<double>(i, j) = 0;
				}
			}
			if ((gradAlpha.at<double>(i, j) < -112.5 && gradAlpha.at<double>(i, j) >= -157.5) ||
				(gradAlpha.at<double>(i, j) >= 22.5 && gradAlpha.at<double>(i, j) < 67.5)) {
				//correctionAlpha.at<double>(i, j) = 4;
				if ((gradValue.at<double>(i + 1, j + 1) > gradValue.at<double>(i, j)) ||
					(gradValue.at<double>(i - 1, j - 1) > gradValue.at<double>(i, j))) {
					gradValueNMS.at<double>(i, j) = 0;
				}
			}

		}
	}
	return gradValueNMS;
}

//! 获得阈值极大值
double MaxValue(Mat image) {
	double max = -1.6e30;
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			if (max < image.at<double>(i, j)) {
				max = image.at<double>(i, j);
			}
		}
	}
	return max;
}

//! 双重阈值过滤
Mat ThresholdFilter(Mat image, double TH, double TL) {
	Mat canny = Mat::zeros(image.rows, image.cols, CV_64FC1);
	for (int i = 1; i < image.rows - 2; i++) {
		for (int j = 1; j < image.cols - 2; j++) {
			if (image.at<double>(i, j) >= TH) {
				for (int x = -1; x <= 1; x++) {
					for (int y = -1; y <= 1; y++) {
						if (image.at<double>(i + x, j + y) >= TL) {
							canny.at<double>(i + x, j + y) = image.at<double>(i + x, j + y);
						}
					}
				}

			}

		}
	}
	return canny;
}