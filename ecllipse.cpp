#define FREEGLUT_STATIC
//#pragma comment(lib, "freeglut_static.lib")
#include <GL\freeglut.h>
#include <cstdlib>
#include <cmath>
#include <cstdio>
#include <iostream>

void init(void);
void Draw_ecllipse(int x0, int y0, int Ra, int Rb);
void Draw_four_ver(int x0, int y0, int x, int y);
void lineSegment(void);

void main(int argc, char *argv[])
{
	int x0, y0, Ra, Rb;
	std::cout << "Please enter the information of an ecllipse:" << std::endl;
	std::cout << "In the order: x0, y0, a, b" << std::endl;
	std::cout << "(Be sure that a,b is bigger than 20 and smaller than 100)" << std::endl;
	std::cin >> x0 >> y0 >> Ra >> Rb;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 300);
	glutInitWindowPosition(50, 100);
	glutCreateWindow("A program to draw the ecllipse");

	init();
	lineSegment();
	Draw_ecllipse(x0, y0, Ra, Rb);
	glutMainLoop();
}

void init(void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(-100, 100, -100, 100);
	glClear(GL_COLOR_BUFFER_BIT);
}

void lineSegment(void)
{
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINES);
	glVertex2i(-100, 0);
	glVertex2i(100, 0);
	glEnd();
	glBegin(GL_LINES);
	glVertex2i(0, 100);
	glVertex2i(0, -100);
	glEnd();
	glFlush();
}

void Draw_four_ver(int x0, int y0, int x, int y)
{
	glColor3f(1.0, 0.0, 0.0);
	glBegin(GL_POINTS);
	glVertex2i(x + x0, y + y0);
	glVertex2i(-x + x0, y + y0);
	glVertex2i(x + x0, -y + y0);
	glVertex2i(-x + x0, -y + y0);
	glEnd();
	glFlush();
}

void Draw_ecllipse(int x0, int y0, int Ra, int Rb)
{
	//glPushMatrix();
	int x = 0;
	int y = Rb;
	int square_b = Rb*Rb;
	int square_a = Ra*Ra;
	double d = square_b + square_a*(0.25 - Rb);
	Draw_four_ver(x0, y0, x, y);
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
		Draw_four_ver(x0, y0, x, y);
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
		Draw_four_ver(x0, y0, x, y);
	}
	//glPopMatrix();
}