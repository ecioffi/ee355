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
	
	static void clear()
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
	static void drawSquare(int x, int y, Color c, int s = 25)
	{
		int d = 32 - s;
		for (int i = 32*x + d; i < (32*(x+1) - d); i++)
		{
			for (int j = 32*y + d; j < (32*(y+1) - d); j++)	
			{
				setPixel(i, j, c);
			}
		}
	}

	static void drawSmallSquare(int x, int y, Color c)
	{
		drawSquare(x, y, c, 21);
	}

	//grid x,y
	static void drawTriangle(int x, int y, Color c)
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
	static void drawCircle(int x, int y, Color c, int r = 81)
	{
		for (int i = 32*x; i < (x+1)*32; i++)
		{
			for (int j = 32*y; j < (y+1)*32; j++)
			{
				if (pow((32*x) + 16 - i, 2.0) + pow((32*y) + 16 - j, 2.0) <= r)
				{
					setPixel(i, j, c);
				}
			}
		}
	}

	static void drawLargeCircle(int x, int y, Color c)
	{
		drawCircle(x, y, c, 121);
	}

	static void drawGrid()
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

	static void show()
	{
		showRGBBMP(image);
	}
};