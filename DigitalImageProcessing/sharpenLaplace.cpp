#include"head.h"

Mat sharpenLaplace(Mat& image) {
	image = cv::imread("D:\\image/book/DIP3E_Original_Images_CH06/Fig0638(a)(lenna_RGB).tif");

	std::vector<cv::Mat> channels;
	cv::split(image, channels);

	cv::imshow("BGR", image);
	cv::imshow("B", channels[0]);
	cv::imshow("G", channels[1]);
	cv::imshow("R", channels[2]);

	int sharpenLaplaceArray[3][3] = { {0,1,0},{1,0,1},{0,1,0} };

	Mat sharpenLaplaceTemplate(3, 3, CV_8UC1, sharpenLaplaceArray);

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			sharpenLaplaceTemplate.at<uchar>(i, j) = sharpenLaplaceArray[i][j];
		}
	}
	Mat ImageB = _convolution(channels[0], sharpenLaplaceTemplate);
	Mat ImageG = _convolution(channels[1], sharpenLaplaceTemplate);
	Mat ImageR = _convolution(channels[2], sharpenLaplaceTemplate);
	cv::imshow("laplaceB", ImageB);
	cv::imshow("laplaceG", ImageG);
	cv::imshow("laplaceR", ImageR);
	cv::Mat mergeChannels[3] = { ImageB, ImageG, ImageR };
	Mat dst;
	cv::merge(mergeChannels, 3, dst);
	dst = _merge(image, dst);
	cv::imshow("ÈÚºÏ", dst);

	cv::waitKey(0);
	return image;
}

Mat _convolution(Mat& image, Mat& image_temp) {
	int w = image.cols;
	int h = image.rows;
	Mat convImage(w, h, CV_8UC1);
	Mat imageEx;
	copyMakeBorder(image, imageEx, 1, 1, 1, 1, cv::BORDER_REFLECT_101);
	imshow("imageEx", imageEx);
	for (int i = 1; i < imageEx.rows - 1; i++) {
		for (int j = 1; j < imageEx.cols - 1; j++) {
			int sum = 0;
			for (int m = 0; m < 3; m++) {
				for (int n = 0; n < 3; n++) {
					sum += imageEx.at<uchar>(i + m - 1, j + n - 1) * image_temp.at<uchar>(m, n);
				}
			}
			int t = sum - 4 * imageEx.at<uchar>(i, j);
			//cout << sum - 4 * image.at<uchar>(i, j) << endl;
			if (t > 0) {
				convImage.at<uchar>(i - 1, j - 1) = t;
			}
			else {
				convImage.at<uchar>(i - 1, j - 1) = 0;
			}

		}
	}
	//cv::imshow("convImage", convImage);
	//cv::waitKey(0);
	return convImage;
}

Mat _merge(Mat& imageA, Mat& imageB) {
	for (int i = 0; i < imageA.rows; i++) {
		for (int j = 0; j < imageA.cols; j++) {
			imageA.at<Vec3b>(i, j)[0] = imageA.at<Vec3b>(i, j)[0] + imageB.at<Vec3b>(i, j)[0] < 255 ? imageA.at<Vec3b>(i, j)[0] + imageB.at<Vec3b>(i, j)[0] : 255;
			imageA.at<Vec3b>(i, j)[1] = imageA.at<Vec3b>(i, j)[1] + imageB.at<Vec3b>(i, j)[1] < 255 ? imageA.at<Vec3b>(i, j)[1] + imageB.at<Vec3b>(i, j)[1] : 255;
			imageA.at<Vec3b>(i, j)[2] = imageA.at<Vec3b>(i, j)[2] + imageB.at<Vec3b>(i, j)[2] < 255 ? imageA.at<Vec3b>(i, j)[2] + imageB.at<Vec3b>(i, j)[2] : 255;
		}
	}

	return imageA;
}