#include"head.h"

Mat rgb2hsi(Mat& image) {
	double θ;
	double H;
	double S;
	double I;
	Mat hsiImage = Mat::zeros(image.size(), CV_8UC3);
	const double PI = acos(-1);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			double r = (double)image.at<Vec3b>(i, j)[2] / 255;
			double g = (double)image.at<Vec3b>(i, j)[1] / 255;
			double b = (double)image.at<Vec3b>(i, j)[0] / 255;


			double numerator = ((2 * r - g - b) / 2);
			double denominator = sqrt((pow((r - g), 2) + (r - b) * (g - b)));

			θ = acos(numerator / denominator);
			H = 360 * θ / (PI * 2);

			if (b > g) {
				H = 360 - H;
			}

			S = 1 - 3.0 * min(b, min(g, r)) / (b + g + r);

			I = (b + g + r) / 3.0;

			hsiImage.at<Vec3b>(i, j)[0] = H / 360 * 255;
			hsiImage.at<Vec3b>(i, j)[1] = S * 255;
			hsiImage.at<Vec3b>(i, j)[2] = I * 255;
		}
	}

	//imshow("hsi", hsiImage);

	waitKey(0);
	return hsiImage;
}