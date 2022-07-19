#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include <vector>

using namespace std;
using namespace cv;


//! -------- Part 6 -------------------------
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
//! ------------------------------------------