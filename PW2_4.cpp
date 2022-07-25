#include<Windows.h>
#include<GL/glut.h>
#include<vector>
#include<fstream>
#include<cstdlib>
using namespace std;

struct Point
{
	int x, y;
};

void reshape(int w, int h);
void display();
void readFromFile();
void lineto(Point p);
void moveto(Point p);
void curve(Point p, int number, int x2, int y2, int z2, int x3, int y3, int z3);
vector<Point> point;
vector<int>code;
Point currentPoint;

int main(int argc, char * argv[])
{
	currentPoint.x = 0; currentPoint.y = 0;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("PW2_4");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, 150, 0, 70);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void curve(Point p, int number, int x2, int y2, int z2, int x3, int y3, int z3)
{
	moveto(point[number]);

	GLfloat curvePoints[4][3] = {
		{currentPoint.x, currentPoint.y, 0},
		{x2, y2, z2},
		{x3, y3, z3},
		{p.x, p.y, 0}
	};

	glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &curvePoints[0][0]);
	glEnable(GL_MAP1_VERTEX_3);

	glBegin(GL_LINE_STRIP);
	for (int i = 0; i <= 30; i++)
		glEvalCoord1f((GLfloat)i / 30.0);
	glEnd();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0, 0, 0);
	readFromFile();
	glColor3d(1, 0, 0);
	for (int i = 0; i < code.size(); i++)
		if (code[i] < 0)
		{
			moveto(point[abs(code[i]) - 1]);
		}
		else
		{
			lineto(point[code[i] - 1]);
		}

	curve(point[6], 5, 40, 15, 0, 40, 25, 0);
	curve(point[12], 11, 85, 30, 0, 85, 30, 0);
	curve(point[15], 14, 135, 30, 0, 135, 30, 0);

	glFlush();
}

void readFromFile()
{
	fstream f("points.txt", ios::in);
	int pointNumber;
	int x, y; Point p;
	f >> pointNumber;
	for (int i = 0; i < pointNumber; i++)
	{
		f >> p.x >> p.y;
		point.push_back(p);
	}
	int movesNumber, m;
	f >> movesNumber;
	for (int i = 0; i < movesNumber; i++)
	{
		f >> m; code.push_back(m);
	}
	f.close();
}

void moveto(Point p) {
	currentPoint.x = p.x; currentPoint.y = p.y;
}

void lineto(Point p) {
	glBegin(GL_LINES);
	glVertex2i(currentPoint.x, currentPoint.y);
	glVertex2i(p.x, p.y);
	glEnd();
	currentPoint.x = p.x; currentPoint.y = p.y;
}