#include"head.h"

void lineFitting() {

	Mat src = Mat(800, 800, CV_8UC3, Scalar(0, 0, 0));
	Point a;
	vector<Point> Points;
	Points.clear();

	//! 生成点图
	for (int i = 0; i < 200; i++) {
		//内点
		int temp = rand() % 800;
		a.x = temp + rand() % 80;
		a.y = temp + rand() % 80;
		circle(src, Point(a.x, a.y), 1, Scalar(0, 255, 0));
		Points.push_back(a);
	}

	for (int i = 0; i < 600; i++) {
		// 外点
		a.x = rand() % 800;
		a.y = rand() % 800;
		circle(src, Point(a.x, a.y), 1, Scalar(0, 255, 0));
		Points.push_back(a);
	}
	cv::imshow("Point Image", src);
	//! 容差 -> 局内点与当前直线的距离
	float tolerance = 60.0;
	//lineFitting_1(src, Points, tolerance);
	lineFitting_2(src, Points, tolerance);
	cv::waitKey(0);
}


//void lineFitting_1(Mat src, vector<Point> Points, float tolerance) {
//
//	int best_inlier_count = 0;
//	int inlier_count = 0;
//
//	//! 临时直线方程参数
//	double k, b;
//
//	//! 最终的直线方程参数
//	double best_k, best_b;
//
//	//! 点到直线距离
//	double dis;
//
//	for (int num1 = 0; num1 < Points.size() - 2; num1++) {
//		for (int num2 = num1 + 1; num2 < Points.size() - 1; num2++) {
//			inlier_count = 0;
//			if (Points[num2].x - Points[num1].x == 0) {
//				continue;
//			}
//			k = (double)(Points[num2].y - Points[num1].y) / (double)(Points[num2].x - Points[num1].x);
//
//			b = (double)(k * Points[num2].x) - Points[num2].y;
//
//			for (int n = 0; n < Points.size(); n++) {
//				dis = abs(k * Points[n].x - Points[n].y + b) / sqrt(1 + k * k);
//				if (dis < tolerance)
//					inlier_count++;
//			}
//
//			if (inlier_count > best_inlier_count) {
//				best_inlier_count = inlier_count;
//				best_k = k;
//				best_b = b;
//			}
//		}
//
//	}
//
//	Point Point_start;
//	Point Point_end;
//	Point_start.x = 0;
//	Point_start.y = best_b;
//	Point_end.x = 320;
//	Point_end.y = 320 * best_k + best_b;
//
//
//	cv::line(src, Point_start, Point_end, Scalar(255, 255, 255), 1);
//	cv::imshow("RACSAC", src);
//}

void lineFitting_2(Mat src, vector<Point> Points, float tolerance) {

	int best_inlier_count = 0;
	int inlier_count = 0;

	//! 临时直线方程参数
	double k, b;

	//! 最终的直线方程参数
	double best_k = 0, best_b = 0;

	//! 点到直线距离
	double distance = 0;

	//! 局内点 point 的 index 值
	vector<int> point_index_best;

	for (int num1 = 0; num1 < Points.size() - 2; num1++) {
		for (int num2 = num1 + 1; num2 < Points.size() - 1; num2++) {
			inlier_count = 0;
			if (Points[num2].x - Points[num1].x == 0) {
				continue;
			}
			k = (double)(Points[num2].y - Points[num1].y) / (double)(Points[num2].x - Points[num1].x);

			b = (double)(k * Points[num2].x) - Points[num2].y;

			vector<int> point_index;
			point_index.clear();
			for (int n = 0; n < Points.size(); n++) {
				distance = abs(k * Points[n].x - Points[n].y + b) / sqrt(1 + k * k);
				if (distance < tolerance) {

					point_index.push_back(n);
					inlier_count++;
				}
			}

			if (inlier_count > best_inlier_count) {
				best_inlier_count = inlier_count;
				best_k = k;
				best_b = b;
				point_index_best.clear();
				point_index_best.assign(point_index.begin(), point_index.end());
			}
		}

	}

	//! 进行最小二乘精确
	Mat X = Mat::zeros(point_index_best.size(), 2, CV_64FC1);
	Mat Y = Mat::zeros(point_index_best.size(), 1, CV_64FC1);
	Mat B = Mat::zeros(2, 1, CV_64FC1);

	for (int i = 0; i < point_index_best.size(); i++) {
		//cout << point_index_best[i] << endl;
		X.at<double>(i, 0) = Points[point_index_best[i]].x;
		X.at<double>(i, 1) = 1;
		Y.at<double>(i, 0) = Points[point_index_best[i]].y;
		circle(src, Point(Points[point_index_best[i]].x, Points[point_index_best[i]].y), 1, Scalar(0, 0, 255));

	}
	//! B = [(X^T · X)^-1] · (X^T · Y)
	Mat BL;
	//! 矩阵乘法
	cv::gemm(X.t(), X, 1, NULL, 0, BL);

	//! 求逆
	cv::invert(BL, BL, DECOMP_LU);

	Mat BR;
	cv::gemm(X.t(), Y, 1, NULL, 0, BR);
	cv::gemm(BL, BR, 1, NULL, 0, B);

	Point Point_start_LS;
	Point Point_end_LS;
	Point_start_LS.x = 0;
	Point_start_LS.y = round(B.at<double>(1));
	Point_end_LS.x = src.cols;
	Point_end_LS.y = round(src.rows * B.at<double>(0) + B.at<double>(1));

	Point Point_start_RACSAC;
	Point Point_end_RACSAC;
	Point_start_RACSAC.x = 0;
	Point_start_RACSAC.y = round(best_b);
	Point_end_RACSAC.x = src.cols;
	Point_end_RACSAC.y = round(src.rows * best_k + best_b);

	cout << "RANSAC_ k = " << best_k << endl;
	cout << "RANSAC_ b = " << best_b << endl;
	cout << "Least Squares k = " << B.at<double>(0) << endl;
	cout << "Least Squares b = " << B.at<double>(1) << endl;

	cv::line(src, Point_start_LS, Point_end_LS, Scalar(255, 100, 0), 1);
	cv::line(src, Point_start_RACSAC, Point_end_RACSAC, Scalar(255, 255, 255), 1);
	cv::imshow("RACSAC + LS", src);
}