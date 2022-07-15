#include"head.h"

const int PI = acos(-1);
Mat hsi2rgb(Mat& image) {
	image = rgb2hsi(image);

	for (int i = 0; i < image.rows; i++) {
		for (int j = 0; j < image.cols; j++) {
			double H = (double)image.at<Vec3b>(i, j)[0] / 255 * 360;
			double S = (double)image.at<Vec3b>(i, j)[1] / 255;
			double I = (double)image.at<Vec3b>(i, j)[2] / 255;
			double R, B, G;

			if (0 <= H < 120) {
				B = I * (1 - S);
				R = I * (1 + S * cos(H * PI / 180) / cos((60 - H) * PI / 180));
				G = 3 * I - (R + B);
			}
			else if (120 <= H < 240) {
				H = H - 120;
				R = I * (1 - S);
				G = I * (1 + S * cos(H * PI / 180) / cos((60 - H) * PI / 180));
				B = 3 * I - (R + G);
			}
			else {
				H = H - 240;
				G = I * (1 - S);
				B = I * ((1 + S * cos(H * PI / 180) / cos((60 - H) * PI / 180)));
				R = 3 * I - (G + B);

			}

			image.at<Vec3b>(i, j)[0] = B * 255;
			image.at<Vec3b>(i, j)[1] = G * 255;
			image.at<Vec3b>(i, j)[2] = R * 255;

		}
	}

	imshow("rgb", image);
	waitKey(0);
	return image;
}