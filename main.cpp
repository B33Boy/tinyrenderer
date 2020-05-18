#include "tgaimage.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

void line(int x0, int y0, int x1, int y1);

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	
	line_naive(0, 0, 20, 50);
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	system("pause");
	return 0;
}

/*
	Assumes x0 < x1 & y0 < y1
*/
void line_naive(int x0, int y0, int x1, int y1)
{
	image.set()
}