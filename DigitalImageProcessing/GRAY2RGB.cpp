#include"head.h"

Mat gray2rgb(Mat& image) {
	//image.convertTo(imageGray, COLOR_RGB2GRAY);
	//image = Mat::zeros(image.size(), image.type());
	resize(image, image, Size(image.cols * 0.5, image.rows * 0.5));

	Mat imageRGB = Mat::zeros(image.size(), 16);
	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			int gray = image.at<uchar>(i, j);
			//cout << gray << endl;

			double grayNor = (double)gray / 255;
			//cout << grayNor << endl;

			//! 颜色偏暗时 --> 海洋 --> 蓝色代替

			if (grayNor >= 0 && grayNor < 0.1) {
				imageRGB.at<Vec3b>(i, j)[0] = 0.9 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[1] = 0.06 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[2] = 0.04 * grayNor * 255;
			}
			//! 灰度中等时 --> 大陆 --> 红代替
			else if (grayNor >= 0.1 && grayNor < 0.2) {
				imageRGB.at<Vec3b>(i, j)[0] = 0.05 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[1] = 0.05 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[2] = 0.9 * grayNor * 255;
			}
			//! 灰度高时 --> 云层 --> 黄代替

			else if (grayNor >= 0.2 && grayNor <= 0.8) {
				imageRGB.at<Vec3b>(i, j)[0] = 0.1 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[1] = 0.8 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[2] = 0.1 * grayNor * 255;
			}
			else if (grayNor >= 0.8 && grayNor <= 1) {
				imageRGB.at<Vec3b>(i, j)[0] = 0.8 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[1] = 0.8 * grayNor * 255;
				imageRGB.at<Vec3b>(i, j)[2] = 0.8 * grayNor * 255;
			}
		}
	}
	imshow("天气伪色彩", imageRGB);
	cv::waitKey(0);

	return imageRGB;
}