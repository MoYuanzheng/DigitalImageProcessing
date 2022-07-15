#include"head.h"

Mat hue(Mat& image) {
	//image = avgImage(image);
	//image = lightImage(image);
	image = darkImage(image);
	return image;
}


//! 10/(1+e^(5-x)) 平淡图像校正曲线 
Mat avgImage(Mat& image) {
	Mat imageTrans = Mat::zeros(image.size(), image.type());

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			double B = (double)image.at<Vec3b>(i, j)[0] / 25.5;
			double G = (double)image.at<Vec3b>(i, j)[1] / 25.5;
			double R = (double)image.at<Vec3b>(i, j)[2] / 25.5;

			imageTrans.at<Vec3b>(i, j)[0] = 10 / (1 + exp(5 - B)) * 25.5;
			imageTrans.at<Vec3b>(i, j)[1] = 10 / (1 + exp(5 - G)) * 25.5;
			imageTrans.at<Vec3b>(i, j)[2] = 10 / (1 + exp(5 - R)) * 25.5;
		}
	}

	imshow("原图", image);
	imshow("色调变换后", imageTrans);
	waitKey(0);

	return image;
}

//! x^2 偏亮图像校正曲线 
Mat lightImage(Mat& image) {
	image = imread("D:\\image/book/DIP3E_Original_Images_CH06/Fig0635(middle_row_left_chalk ).tif");
	Mat imageTrans = Mat::zeros(image.size(), image.type());

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			double B = (double)image.at<Vec3b>(i, j)[0] / 255;
			double G = (double)image.at<Vec3b>(i, j)[1] / 255;
			double R = (double)image.at<Vec3b>(i, j)[2] / 255;

			imageTrans.at<Vec3b>(i, j)[0] = pow(B, 2) * 255;
			imageTrans.at<Vec3b>(i, j)[1] = pow(G, 2) * 255;
			imageTrans.at<Vec3b>(i, j)[2] = pow(R, 2) * 255;
		}
	}

	imshow("原图", image);
	imshow("色调变换后", imageTrans);
	waitKey(0);

	return image;
}

//! x^(1/2) 偏暗图像校正曲线 
Mat darkImage(Mat& image) {
	image = imread("D:\\image/book/DIP3E_Original_Images_CH06/Fig0635(bottom_left_stream).tif");
	Mat imageTrans = Mat::zeros(image.size(), image.type());

	for (int i = 0; i < image.cols; i++) {
		for (int j = 0; j < image.rows; j++) {
			double B = (double)image.at<Vec3b>(i, j)[0] / 255;
			double G = (double)image.at<Vec3b>(i, j)[1] / 255;
			double R = (double)image.at<Vec3b>(i, j)[2] / 255;

			imageTrans.at<Vec3b>(i, j)[0] = sqrt(B) * 255;
			imageTrans.at<Vec3b>(i, j)[1] = sqrt(G) * 255;
			imageTrans.at<Vec3b>(i, j)[2] = sqrt(R) * 255;
		}
	}

	imshow("原图", image);
	imshow("色调变换后", imageTrans);
	waitKey(0);

	return image;
}