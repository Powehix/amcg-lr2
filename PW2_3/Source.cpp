#include<Windows.h>
#include<GL/glut.h>
#include<vector>
#include<fstream>
#include<cstdlib>
using namespace std;

void reshape(int w, int h);
void display();

int main(int argc, char * argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("PW2_3");
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
	gluOrtho2D(0, 100, 0, 60);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display()
{
	glClearColor(1, 1, 1, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1, 0, 0);
	glLineWidth(4);

	GLfloat leftPoints[4][3] = {
		{50, 10, 0},
		{30, 25, 0},
		{15, 65, 0},
		{50, 40, 0}
	};

	GLfloat rightPoints[4][3] = {
		{50, 10, 0},
		{70, 25, 0},
		{85, 65, 0},
		{50, 40, 0}
	};
	
	GLfloat node[8] = { 0, 0, 0, 0, 1, 1, 1, 1 };

	//левая кривая
	GLUnurbs* leftNurbs = gluNewNurbsRenderer();
	gluBeginCurve(leftNurbs);
	gluNurbsCurve(leftNurbs, 8, &node[0], 3, &leftPoints[0][0], 4, GL_MAP1_VERTEX_3);
	gluEndCurve(leftNurbs);

	//правая кривая
	GLUnurbs* rightNurbs = gluNewNurbsRenderer();
	gluBeginCurve(rightNurbs);
	gluNurbsCurve(rightNurbs, 8, &node[0], 3, &rightPoints[0][0], 4, GL_MAP1_VERTEX_3);
	gluEndCurve(rightNurbs);

	glutSwapBuffers();
	gluDeleteNurbsRenderer(leftNurbs);
	gluDeleteNurbsRenderer(rightNurbs);

	glFlush();
}