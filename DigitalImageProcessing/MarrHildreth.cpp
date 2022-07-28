#include "head.h"

void MarrHildrethEdge(Mat image, int kSize, double sigma)
{
	kSize = 25;
	sigma = 4;
	image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1022(a)(building_original).tif", 0);

	//使用 Laplacian of Gaussian 函数计算卷积模板
	int kernel_dia = kSize * 2 + 1;
	Mat kernel(kernel_dia, kernel_dia, CV_64FC1);
	for (int i = -kSize; i <= kSize; i++) {
		for (int j = -kSize; j <= kSize; j++) {
			kernel.at<double>(i + kSize, j + kSize) = exp(-(pow(i, 2) + pow(j, 2)) / (pow(sigma, 2) * 2))
				* ((pow(i, 2) + pow(j, 2) - 2 * pow(sigma, 2)) / (2 * pow(sigma, 4)));

		}
	}
	//卷积
	Mat LoG(image.rows - kSize * 2, image.cols - kSize * 2, CV_64FC1);
	double max = -1.6e-30;
	for (int i = kSize; i < image.rows - kSize; i++) {
		for (int j = kSize; j < image.cols - kSize; j++) {
			double sum = 0;
			for (int x = -kSize; x <= kSize; x++) {
				for (int y = -kSize; y <= kSize; y++) {
					sum += image.at<uchar>(i + x, j + y) * kernel.at<double>(x + kSize, y + kSize);
				}
			}
			LoG.at<double>(i - kSize, j - kSize) = sum;
			if (max < sum) {
				max = sum;
			}
		}
	}

	Mat laNor;

	Mat marr0 = Mat::zeros(LoG.size(), CV_64FC1);
	Mat marr0_04 = Mat::zeros(LoG.size(), CV_64FC1);
	normalize(LoG, laNor, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
	imshow("laNor", laNor);
	//遍历LoG算子

	for (int i = 1; i < LoG.rows - 1; i++) {
		for (int j = 1; j < LoG.cols - 1; j++) {
			if ((LoG.at<double>(i - 1, j) * LoG.at<double>(i + 1, j) < 0)
				|| (LoG.at<double>(i, j - 1) * LoG.at<double>(i, j + 1) < 0)
				|| (LoG.at<double>(i - 1, j + 1) * LoG.at<double>(i + 1, j - 1) < 0)
				|| (LoG.at<double>(i - 1, j - 1) * LoG.at<double>(i + 1, j + 1) < 0)) {
				marr0.at<double>(i, j) = LoG.at<double>(i, j);
			}
			if (LoG.at<double>(i, j) > max * 0.035
				&& ((LoG.at<double>(i - 1, j) * LoG.at<double>(i + 1, j) < 0)
					|| (LoG.at<double>(i, j - 1) * LoG.at<double>(i, j + 1) < 0)
					|| (LoG.at<double>(i - 1, j + 1) * LoG.at<double>(i + 1, j - 1) < 0)
					|| (LoG.at<double>(i - 1, j - 1) * LoG.at<double>(i + 1, j + 1) < 0))) {
				marr0_04.at<double>(i, j) = LoG.at<double>(i, j);
			}
		}
	}
	imshow("marr0", marr0);
	imshow("marr0_04", marr0_04);
	waitKey(0);
}