#include <iostream>
#include <fstream>
#include <string>

#include "Vec3.h"

int main()
{
	std::ofstream ppmFile("out.ppm");
	ppmFile << "P3\n";

	int nCols = 200;
	int nRows = 100;
	ppmFile << nCols << " " << nRows <<"\n";
	ppmFile << "255\n";

	// Write pixels left to write and bottom to top
	for (int j = nRows - 1; j >= 0; j--)
	{
		for (int i = 0; i < nCols; i++)
		{
			// Convert rgb to a val between 0 and 1
			/*float r = i / float(nCols);
			float g = j / float(nRows);
			float b = 0.2f;*/
			Vec3f rgbBetween0And1(i / float(nCols), j / float(nRows), 0.2f);

			// Convert from 0-1 range back to 0-255 range
			// Leaving float results in small numbers, not multiplying by 
			// 255.9 results in all 0
			/*int ir = int(255.9*r);
			int ig = int(255.9*g);
			int ib = int(255.9*b);*/
			Vec3i rgbBetween0And255(255.9*rgbBetween0And1.r, 255.9*rgbBetween0And1.g, 255.9*rgbBetween0And1.b);

			ppmFile << rgbBetween0And255.r << " " << rgbBetween0And255.g << " " << rgbBetween0And255.b << "\n";
		}
	}

	return 0;
}