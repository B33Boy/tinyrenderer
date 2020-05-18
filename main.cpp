#include "tgaimage.h"
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);


/*
	Pros: 
		It works for lines with slopes > 1 and less than 1)
	Cons:
		Increemnt is a hindrance as we have to set it manually
*/
void line_naive(TGAImage &image, float x0, float y0, float x1, float y1, float increment, const TGAColor& colour)
{
	float dx = x1 - x0;
	float dy = y1 - y0;

	for (float i=0.f; i<1.f; i+=increment)
	{
		float x = x0 + i * dx;
		float y = y0 + i * dy;
		
		image.set(x, y, colour);
	}
}

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	
	line_naive(image, 0, 50, 100, 50, 0.01f, red); // Hor line
	line_naive(image, 50, 0, 50, 100, 0.01f, red); // Ver line
	line_naive(image, 20, 0, 80, 20, 0.01f, red); // Slight positive slope 
	line_naive(image, 20, 80, 80, 20, 0.01f, red); // Slight negative slope
	line_naive(image, 20, 0, 30, 100, 0.01f, red); // Large positive slope 
	line_naive(image, 20, 100, 30, 20, 0.01f, red); // Large negative slope
	

	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	system("pause");
	return 0;
}
