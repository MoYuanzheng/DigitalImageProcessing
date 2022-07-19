#include"head.h"
int main() {
	Mat image = imread("D:\\image/sample.png");
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

<<<<<<< HEAD
<<<<<<< HEAD
	image = colorDevision(image);
=======
>>>>>>> parent of af909da (utf-8)
=======
	image = colorDevision(image);
>>>>>>> e994950c105769b35eb4ed86d4e8615f1191beb3

	return 0;
}