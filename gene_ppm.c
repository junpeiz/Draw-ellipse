#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
 
const int WIDTH = 256;
const int HEIGHT = 128;
const unsigned char red[3] = { 255, 0, 0 };
const unsigned char white[3] = { 255, 255, 255 };
const unsigned char black[3] = { 0, 0, 0 };

void Draw_ecllipse(unsigned char (*p)[3], int x0, int y0, int Ra, int Rb);
static int PPMWriteImage(const char* filePath, const unsigned char* buffer, unsigned int width, unsigned int height);
void Draw_cordinary(unsigned char (*p)[3]);
void Draw_four_ver(unsigned char (*p)[3], int x0, int y0, int x, int y);

int main(void)
{
	unsigned char testImage[HEIGHT][WIDTH][3];
	unsigned int i = WIDTH * HEIGHT;
	unsigned char (*p)[3] = &testImage[0][0];
	unsigned char (*temp)[3] = &testImage[0][0];
	int x0 = 30;
	int y0 = 20;
	int Ra = 90;
	int Rb = 30;
	while(i--)
		memcpy(temp++, black, sizeof(black));
	Draw_cordinary(&testImage[0][0]);	
	Draw_ecllipse(&testImage[0][0], x0, y0, Ra, Rb);
	PPMWriteImage("ZJP_3140102286_A1.ppm", &testImage[0][0][0], WIDTH, HEIGHT);
	return 0;
}

void Draw_cordinary(unsigned char (*p)[3])
{
	int cenx = HEIGHT/2;
	int ceny = WIDTH/2;
	int x, y;
	for(x = 0; x < HEIGHT; x++)
		for(y = 0; y < WIDTH; y++)
			if(x == cenx || y == ceny)
				memcpy(p + x*WIDTH + y, white, sizeof(white));
}

void Draw_four_ver(unsigned char (*p)[3], int x0, int y0, int x, int y)
{
	int cenx = HEIGHT/2;
	int ceny = WIDTH/2;
	int x1 = x + x0;
	int y1 = y + y0;
	int x2 = -x + x0;
	int y2 = y + y0;
	int x3 = x + x0;
	int y3 = -y + y0;
	int x4 = -x + x0;
	int y4 = -y + y0;
	memcpy(p + (cenx-y1)*WIDTH + (ceny+x1), red, sizeof(red));
	memcpy(p + (cenx-y2)*WIDTH + (ceny+x2), red, sizeof(red));
	memcpy(p + (cenx-y3)*WIDTH + (ceny+x3), red, sizeof(red));
	memcpy(p + (cenx-y4)*WIDTH + (ceny+x4), red, sizeof(red));
}

void Draw_ecllipse(unsigned char (*p)[3], int x0, int y0, int Ra, int Rb)
{
	int x = 0;
	int y = Rb;
	int square_b = Rb*Rb;
	int square_a = Ra*Ra;
	double d = square_b + square_a*(0.25 - Rb);
	Draw_four_ver(p, x0, y0, x, y);
	while (square_b*(x + 1) < square_a*(y - 0.5)){
		if (d >= 0){
			d = d + square_b*(2 * x + 3) + square_a*(2 - 2 * y);
			x = x + 1;
			y = y - 1;
		}
		else{
			d = d + square_b*(2 * x + 3);
			x = x + 1;
			y = y;
		}
		Draw_four_ver(p, x0, y0, x, y);
	}
	d = square_b*(x + 0.5)*(x + 0.5) + square_a*(y - 1)*(y - 1) - square_a*square_b;
	while (y > 0){
		if (d >= 0){
			d = d + square_a*(-2 * y + 3);
			x = x;
			y = y - 1;
		}
		else{
			d = d + square_b*(2 * x + 2) + square_a*(-2 * y + 3);
			x = x + 1;
			y = y - 1;
		}
		Draw_four_ver(p, x0, y0, x, y);
	}
	//glPopMatrix();
}

static int PPMWriteImage(const char* filePath, const unsigned char* buffer, unsigned int width, unsigned int height)
{
	FILE* fp;
	unsigned int total = width * height * 3;

	assert(filePath != NULL);
	assert(buffer != NULL);

	fp = fopen(filePath, "wb");
	if (fp == NULL)
	{
		fprintf(stderr, "Open target image file [%s] failed!\n", filePath);
		return 0;
	}

	/* Write file header */
	fprintf(fp, "P3 %u %u 255\n", width, height);

	/* Write file content */
	while (total-- > 0)
	{
		fprintf(fp, " %u", *buffer++);
	}

	fclose(fp);
	return 1;
}
