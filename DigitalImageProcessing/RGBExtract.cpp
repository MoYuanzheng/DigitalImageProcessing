#include"head.h"

void rgbExtract(Mat& image) {
	Mat red = Mat::zeros(image.size(), image.type());
	Mat green = Mat::zeros(image.size(), image.type());
	Mat blue = Mat::zeros(image.size(), image.type());

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			red.at<Vec3b>(i, j)[2] = image.at<Vec3b>(i, j)[2];
			green.at<Vec3b>(i, j)[1] = image.at<Vec3b>(i, j)[1];
			blue.at<Vec3b>(i, j)[0] = image.at<Vec3b>(i, j)[0];
		}
	}
	imshow("B", blue);
	imshow("G", green);
	imshow("R", red);
	waitKey(0);
}