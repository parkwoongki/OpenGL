// Mouse Callback Example.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>

GLint TopLeftX, TopLeftY, BottomRightX, BottomRightY;

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT);

	glViewport(0, 0, 300, 300); // 0,0 으로 시작해서 300 300 만큼 보여줌 얘가 없으면 고정이 안되서 윈도우 창 변경할때마다 모양이 바뀜

	glColor3f(0.5f, 0.0f, 0.5f); // 빨간색 출력 float형으로 실수의 기본형은 double임
	glBegin(GL_POLYGON);
		glVertex3f(TopLeftX/300.0, (300-TopLeftY)/300.0, 0.0);
		glVertex3f(TopLeftX/300.0, (300-BottomRightY)/300.0, 0.0);
		glVertex3f(BottomRightX/300.0, (300-BottomRightY)/300.0, 0.0);
		glVertex3f(BottomRightX/300.0, (300-TopLeftY)/300.0, 0.0);
	glEnd();

	glFlush();
}

void MyMouseClick(GLint Button, GLint State, GLint X, GLint Y) { // 클릭했을 때의 콜백 함수, 누른 버튼의 종류가 무엇인지, 상태(눌렀는지 때어졌는지) 이하 좌표 X,Y
	if (Button == GLUT_LEFT_BUTTON && State == GLUT_DOWN) {
		TopLeftX = X;
		TopLeftY = Y;
	}
}

void MyMouseMove(GLint X, GLint Y) {
	BottomRightX = X;
	BottomRightY = Y;
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB); // 디스플레이 칼라모드?
	glutInitWindowSize(300, 300); // 윈도우 사이즈 조정 폭과 높이를 300화소로 하라는 것
	glutInitWindowPosition(0, 0); // 처음 시작 위치 (원점) 이건 창의 위치임
	glutCreateWindow("Mouse Callback Example (Rubber Band)"); // 이거 있어야 기본 실행됨

	glClearColor(1.0, 1.0, 1.0, 1.0); // 검정색으로! 마지막 파라미터는 불투명도를 나타냄 1이기 때문에 불투명한 것으로 나온다.
	glMatrixMode(GL_PROJECTION); // 투상 행렬을 변환 대상으로 설정
	glLoadIdentity(); // 행렬에 항등행렬을 실어라
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

	glutDisplayFunc(MyDisplay); // 이거 없으면 화면에 안뜸!! 이벤트에 콜백함수를 넣는, 화면에 그리는 함수를 콜백함수 형태로 실행한다. 이벤트 구동 방식
	glutMouseFunc(MyMouseClick);
	glutMotionFunc(MyMouseMove);
	glutMainLoop(); // 이것을 통해서 어떤 이벤트가 발생하면 운영체제가 보고 등록된 콜백함수를 호출해주는 것

	return 0;
}

// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
