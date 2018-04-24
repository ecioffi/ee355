#pragma once

#include <cmath>

#include "bmplib.h"
#include "entity.h"
#include "types.h"

namespace {
	unsigned char image[SIZE][SIZE][RGB];

	void setPixel(int x, int y, int r, int g, int b)
	{
		image[x][y][0] = r;
		image[x][y][1] = g;
		image[x][y][2] = b;
	}

	void setPixel(int x, int y, Color c)
	{
		setPixel(x, y, c.r, c.g, c.b);
	}
};

namespace GFX {
	
	void clear()
	{
		for (int x = 0; x < SIZE; x++)
		{
			for (int y = 0; y < SIZE; y++)
			{
				setPixel(x, y, Colors::White);
			}
		}
	}

	//grid x,y
	void drawSquare(int x, int y, Color c)
	{
		for (int i = 32*x + 8; i < (32*x + 24); i++)
		{
			for (int j = 32*y + 8; j < (32*y + 24); j++)	
			{
				setPixel(i, j, c);
			}
		}
	}

	//grid x,y
	void drawTriangle(int x, int y, Color c)
	{
		int diff = 0;
		for (int i = 32*x + 8; i < (32*x + 24); i++)
		{
			for (int j = 32*y + 8 + diff/2; j < (32*y + 24 - diff/2); j++)	
			{
				setPixel(i, j, c);
			}
			diff++;
		}
	}

	//grid x,y
	void drawCircle(int x, int y, Color c)
	{
		for (int i = 32*x; i < (x+1)*32; i++)
		{
			for (int j = 32*y; j < (y+1)*32; j++)
			{
				if (pow((32*x) + 16 - i, 2.0) + pow((32*y) + 16 - j, 2.0) <= 49)
				{
					setPixel(i, j, c);
				}
			}
		}

	}

	void drawGrid()
	{
		//draw y-gird lines
		for (int x = 0; x < SIZE; x+=32)
		{
			for (int y = 0; y < SIZE; y++)
			{
				setPixel(x, y, Colors::Black);
			}
		}
		//draw x-gird lines
		for (int y = 0; y < SIZE; y+=32)
		{
			for (int x = 0; x < SIZE; x++)
			{
				setPixel(x, y, Colors::Black);
			}
		}
	}

	void show()
	{
		showRGBBMP(image);
	}
};