#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <ctime>
#include <string>
#include <vector>
#include<math.h>

using namespace std;
using namespace cv;


//! -------- Part 6 Start-------------------------
void rgbExtract(Mat& image);
Mat rgb2hsi(Mat& image);
Mat hsi2rgb(Mat& image);
Mat gray2rgb(Mat& image);

Mat hue(Mat& image);
Mat avgImage(Mat& image);
Mat lightImage(Mat& image);
Mat darkImage(Mat& image);

Mat colorSmooth(Mat& image);

Mat sharpenLaplace(Mat& image);
Mat _convolution(Mat& image, Mat& image_temp);
Mat _merge(Mat& imageA, Mat& imageB);
Mat colorDevision(Mat& image);
Mat hough(Mat image);
//! -------- Part 6 End-------------------------


//! -------- Part 10 Start-------------------------
Mat outlierCheck(Mat& image);
Mat _convolution2(Mat& image, Mat& image_temp);
Mat binarization(Mat& image, double flag);
Mat lineCheck(Mat& image);
Mat _convolution3(Mat& image, Mat& image_temp);
void edgeModel(Mat image);
Mat firstDerivative(Mat& image);
Mat secondDerivative(Mat& image);
Mat GaussNoisy(Mat& image, double average, double stdDev);
Mat Gradient2D(Mat& image);
Mat _convolution4(Mat image, double sobel[][3]);
void MarrHildrethEdge(Mat image, int kSize, double sigma);

void canny(Mat image);
Mat GuassianKernel(double sigma);
Mat _convolution5(Mat image, Mat kernel);
Mat GradientValue(Mat image);
Mat GradientAlpha(Mat image);
Mat _convolution6(Mat image, double sobel[][3]);
Mat AlphaDetermine(Mat gradImage, Mat gradAlpha);

double MaxValue(Mat image);
Mat ThresholdFilter(Mat image, double TH, double TL);

//! -------- Part 10 End-------------------------
//! -------- Home 4 Start-------------------------
Mat harris(Mat image);
Mat susan(Mat image);
Mat USAN(Mat image, int temp[][7]);
Mat USAN2(Mat image, int temp[][7]);

//! -------- Hmoe 4 -End-------------------------
//! 
//! -------- 实习 Start-------------------------

void lineFitting();
void lineFitting_1(Mat src, vector<Point> Points, float tolerance);
void Plane();
void lineFitting_2(Mat src, vector<Point> Points, float tolerance);
//! -------- 实习 -End-------------------------
//! 