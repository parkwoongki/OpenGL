#include <glut.h>
#include <time.h>

int Day = 0, Time = 0;
int IsWire = true;
int IsParallel = true;

void CoveredPlanetFace() {
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

void MyTimer(int value) {
	Day = (Day + 5) % 360;
	Time = (Time + 10) % 360;
	glutPostRedisplay();
	glutTimerFunc(1000, MyTimer, 1);
}

void MyDisplay()
{
	CoveredPlanetFace();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	if (!IsParallel)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glPushMatrix();
		gluPerspective(60.0, 1.0, 1.0, 100.0);

		gluLookAt(0.0, 0.0, 1.8, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();

	glColor3f(1.0f, 0.3f, 0.3f);
	if (IsWire)
		glutWireSphere(0.2, 20, 16);
	else
		glutSolidSphere(0.2, 20, 16);
	glPushMatrix();
	glRotatef((GLfloat)Day, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.7f, 0.0f, 0.0f);
	glColor3f(0.3f, 0.3f, 1.0f);
	if (IsWire)
		glutWireSphere(0.1, 10, 8);
	else
		glutSolidSphere(0.1, 10, 8);
	glPushMatrix();
	glRotatef((GLfloat)Time, 0.0f, 1.0f, 0.0f);
	glTranslatef(0.2f, 0.0f, 0.0f);
	glColor3f(0.9f, 0.8f, 0.2f);
	if (IsWire)
		glutWireSphere(0.04, 10, 8);
	else
		glutSolidSphere(0.04, 10, 8);
	glPopMatrix();
	glPopMatrix();

	if (!IsParallel)
	{
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
	}

	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();

	glutSwapBuffers();
}

void MyMainMenu(int entryID)
{
	if (entryID == 1)
		IsWire = true;
	else if (entryID == 2)
		IsWire = false;
	else if (entryID == 3)
		IsParallel = true;
	else if (entryID == 4)
		IsParallel = false;
	else
		exit(0);

	glutPostRedisplay();
}
int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(400, 400);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("OpenGL Sample Drawing");
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddMenuEntry("Wireframe Rendering", 1);
	glutAddMenuEntry("Solid Rendering", 2);
	glutAddMenuEntry("Parallel Projection", 3);
	glutAddMenuEntry("Perspective Projection", 4);
	glutAddMenuEntry("Exit", 5);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	glutDisplayFunc(MyDisplay);
	glutTimerFunc(1000, MyTimer, 1);

	glutMainLoop();

	return 0;
}