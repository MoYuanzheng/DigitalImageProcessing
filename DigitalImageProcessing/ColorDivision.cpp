#include"head.h"


//! 设 欧式距离 D = 12
Mat colorDevision(Mat& image) {
	image = cv::imread("D:\\image/book/DIP3E_Original_Images_CH06/Fig0642(a)(jupiter_moon_original).tif");
	Mat roi = cv::imread("D:\\image/jupiter_roi.png");

	Mat mean, stdDev;
	cv::meanStdDev(roi, mean, stdDev);
	imshow("mean", mean);
	Mat result(image.size(), CV_8UC3);

	double meanB = mean.at<Vec3b>(0, 0)[0];
	double meanG = mean.at<Vec3b>(0, 0)[1];
	double meanR = mean.at<Vec3b>(0, 0)[2];


	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			int B = image.at<Vec3b>(i, j)[0];
			int G = image.at<Vec3b>(i, j)[1];
			int R = image.at<Vec3b>(i, j)[2];

			//! 欧氏距离识别效果不好 故放弃
			//double d = sqrt(pow((B - meanB), 2) + pow((G - meanG), 2) + pow((R - meanR), 2));
			double dR = pow((R - meanR), 2);
			double dB = pow((B - meanB), 2);
			double dG = pow((G - meanG), 2);

			if (dR <= 600 && dB <= 400 && dG <= 6000) {
				result.at<Vec3b>(i, j)[0] = 255;
				result.at<Vec3b>(i, j)[1] = 255;
				result.at<Vec3b>(i, j)[2] = 255;
			}
			else {
				result.at<Vec3b>(i, j)[0] = 0;
				result.at<Vec3b>(i, j)[1] = 0;
				result.at<Vec3b>(i, j)[2] = 0;
			}
		}
	}

	imshow("分割图像", result);
	waitKey(0);
	return result;
}