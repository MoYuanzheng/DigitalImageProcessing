#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

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
void _sobel();
//! -------- Part 10 End-------------------------