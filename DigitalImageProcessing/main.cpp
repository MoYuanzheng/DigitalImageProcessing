#include"head.h"
int main() {
	//Mat image = imread("D:\\image/sample.png", 0);
	Mat image = imread("D:\\image/book/DIP3E_Original_Images_CH10/Fig1036(a)(original_septagon).tif", 0);
	if (image.empty()) {
		printf("could not load image...\n");
		return -1;
	}


	//! ---第六章 彩色图像处理
	//rgb2hsi(image);
	//rgbExtract(image);
	//hsi2rgb(image);
	//Mat rainRgb = gray2rgb(rain);
	//image = hue(image);
	//image = colorSmooth(image);
	//image = sharpenLaplace(image);
	//! ---结束


	//! ---第十章 图像分割
	//image = lineCheck(image);
	//image = outlierCheck(image);
	//edgeModel(image);
	//image = Gradient2D(image);
	//MarrHildrethEdge(image, 2, 4);
	//canny(image);
	//image = hough(image);
	//image = harris(image);
	//image = susan(image);

	lineFitting();
	//Plane();
	return 0;
}