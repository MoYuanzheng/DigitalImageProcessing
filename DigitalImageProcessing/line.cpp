#include"head.h"
//! RANSEC 第一版
//! 容差（若（该点与直线距离 < 容差）=> 该点为 inlier）需要手动设置
//! 循环结束条件：inlier 数量大于 40（手动设置的参数）

void lineFitting_1() {
	Mat src = Mat(320, 320, CV_8UC3, Scalar(0, 0, 0));

	Point a;
	vector<Point> Points;
	Points.clear();

	//! 生成点图
	for (int i = 0; i < 100; i++) {
		//! 0 - 300 的随机数 -> 内点
		int temp = rand() % 300;
		a.x = temp + rand() % 10;
		a.y = temp + rand() % 20;
		circle(src, Point(a.x, a.y), 1, Scalar(0, 0, 255));
		Points.push_back(a);
	}

	for (int i = 0; i < 100; i++) {
		//! 0 - 300 的随机数 -> 外点
		a.x = rand() % 300;
		a.y = rand() % 300;
		circle(src, Point(a.x, a.y), 1, Scalar(0, 255, 0));
		Points.push_back(a);
	}

	cv::imshow("Point Image", src);
	//! --------------------------------------------------------

	//! 容差 -> 局内点与当前直线的距离
	float tolerance = 10.0;

	int best_inlier_count = 0;
	int inlier_count = 0;

	//! 临时直线方程参数
	double k, b;

	//! 最终的直线方程参数
	double best_k, best_b;

	//! 点到直线距离
	double dis;

	for (int num1 = 0; num1 < Points.size() - 2; num1++) {
		for (int num2 = num1 + 1; num2 < Points.size() - 1; num2++) {
			inlier_count = 0;
			if (Points[num2].x - Points[num1].x == 0) {
				continue;
			}
			k = (double)(Points[num2].y - Points[num1].y) / (double)(Points[num2].x - Points[num1].x);

			b = (double)(k * Points[num2].x) - Points[num2].y;

			for (int n = 0; n < Points.size(); n++) {
				dis = abs(k * Points[n].x - Points[n].y + b) / sqrt(1 + k * k);
				if (dis < tolerance)
					inlier_count++;
			}

			if (inlier_count > best_inlier_count) {
				best_inlier_count = inlier_count;
				best_k = k;
				best_b = b;
			}
		}

	}

	Point Point_start;
	Point Point_end;
	Point_start.x = 0;
	Point_start.y = best_b;
	Point_end.x = 320;
	Point_end.y = 320 * best_k + best_b;

	cv::line(src, Point_start, Point_end, Scalar(255, 255, 255), 1);
	cv::imshow("Fitting Image", src);

	cv::waitKey(0);
}