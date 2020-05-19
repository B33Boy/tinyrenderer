#include "tgaimage.h"
#include <math.h>
#include <iostream>

const TGAColor white = TGAColor(255, 255, 255, 255);
const TGAColor red = TGAColor(255, 0, 0, 255);

/*
	Pros: 
		It works for lines with slopes > 1 and less than 1)
	Cons:
		Increment is a hindrance as we have to set it manually
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

/*
	Pros:
		Increment computed manually
	Cons:
		Not as accurate as Bresenham's algorithm
		
*/
void line_dda(TGAImage& image, float x0, float y0, float x1, float y1, const TGAColor& colour)
{
	// Corrects the order of input points
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	float dx = x1 - x0;
	float dy = y1 - y0; 
	float increment = dx;

	if (abs(dy) > abs(dx))
	{
		increment = std::abs(dy);
	}
	
	dx = dx / increment;
	dy = dy / increment;

	// only draw if increment is greater than 1	
	int i=1;
	for (int i=1; i<=increment; i++)
	{
		image.set(x0, y0, colour);
		x0 += dx;
		y0 += dy;
	} 

}


/*
	Pros:
		Fast because we deal with integers
	Cons:
		Meant for simple lines, not smooth

*/
void line_bresenham(TGAImage& image, int x0, int y0, int x1, int y1, const TGAColor& colour)
{
	// If line is greater slope than m=1
	// Reflect it across y = x to get transpose
	bool steep = false;
	if (abs(x0 - x1) < abs(y0 - y1))
	{
		std::swap(x0, y0);
		std::swap(x1, y1);
		steep = true;
	}

	// Corrects the order of input points
	if (x0 > x1)
	{
		std::swap(x0, x1);
		std::swap(y0, y1);
	}

	int dx = x1 - x0;
	int dy = y1 - y0;

	// This is the intial slope
	float derror = abs(dy / float(dx));
	float error = 0;

	for (int y=y0; int x=x0; x <= x1; x++)
	{
		if (steep)
		{
			image.set(y, x, colour);
		}
		else
		{
			image.set(x, y, colour);
		}

		// Add to the slope, if the slope is greater than 0.5
		//	then we can see whether to choose y_current or y_current + 1
		error += derror;
		if (error > 0.5)
		{
			y += (y1 > y0 ? 1 : -1);
			error -= 1.0;
		}
	}

}

int main(int argc, char** argv) {
	TGAImage image(100, 100, TGAImage::RGB);
	line_bresenham(image, 0, 50, 100, 50, red); // Hor line
	line_bresenham(image, 50, 0, 50, 100, red); // Ver line
	line_bresenham(image, 20, 0, 80, 20, red); // Slight positive slope 
	line_bresenham(image, 20, 80, 80, 60, red); // Slight negative slope
	line_bresenham(image, 20, 0, 40, 100, red); // Large positive slope 
	line_bresenham(image, 20, 100, 30, 20, red); // Large negative slope
	line_bresenham(image, 0, 0, 100, 100, red); // Slope 1
	
	image.flip_vertically(); // i want to have the origin at the left bottom corner of the image
	image.write_tga_file("output.tga");

	system("pause");
	return 0;
}
