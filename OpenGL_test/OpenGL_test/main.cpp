#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <vector>

#define DELTA_X 0.01f
#define X0 1.0f

using namespace std;

struct tag_point
{
	double x; 
	double y;
};
typedef struct tag_point point;
vector<point> point_set;
double linear(double a, double b, double x)
{
	double y = a * X0 + b;
	double delta_y = a * DELTA_X;

	for (int i = (x - X0) / DELTA_X; i > 0; i--)
	{
		y += delta_y;
	}
	return y;
}

double quadratic(double a, double b, double c, double x)
{
	double y = a * X0 * X0 + b * X0 + c;
	double delta_y = 0.0f;
	double delta = X0;

	for (int i = (x - X0) / DELTA_X; i > 0; i--)
	{
		delta_y = DELTA_X * linear(2 * a, b, delta);
		y += delta_y;
		delta += DELTA_X;
	}
	return y;
}

double cubic(double a, double b, double c, double d, double x)
{
	double y = a * X0 * X0 * X0 + b * X0 * X0 + c * X0 + d;
	double delta_y = 0.0f;
	double delta = X0;
	point point_tmp;
	point_tmp.x = X0;
	point_tmp.y = y;
	point_set.push_back(point_tmp);

	for (int i = (x - X0) / DELTA_X; i > 0; i--)
	{
		delta_y = DELTA_X * quadratic(3 * a, 2 * b, c, delta);
		y += delta_y;
		delta += DELTA_X;
		point_tmp.x = delta;
		point_tmp.y = y;
		point_set.push_back(point_tmp);
	}
	return y;
}

void myDisplay(void) {
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_LINES);
	glVertex2f(-1.0f, 0.0f);
	glVertex2f(1.0f, 0.0f);
	glVertex2f(0.0f, -1.0f);
	glVertex2f(0.0f, 1.0f);

	glEnd();

	glBegin(GL_LINE_STRIP);
	for (vector<point>::iterator iter = point_set.begin(); iter != point_set.end(); iter++)
	{
		glVertex2f((*iter).x / 10, (*iter).y / 1000.0);
	}

	glEnd();
	glFlush();
}

int main(int argc, char *argv[]) {

	cubic(1, 1, 1, 1, 10);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(500, 500);
	glutCreateWindow("º¯ÊýÍ¼Ïñ");

	glutDisplayFunc(&myDisplay);
	
	glutMainLoop();
	return 0;
}