#include"head.h"
#include"part_6.h"

int main() {

	Mat image = imread("D:\\image/sample.png");
	cout << image.type();
	if (image.empty()) {
		printf("could not load image...\n");
		return -1;
	}



	//rgb2hsi(image);
	//rgbExtract(image);
	//hsi2rgb(image);
	//Mat rainRgb = gray2rgb(rain);
	//image = hue(image);
	return 0;
}


