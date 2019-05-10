// PWG201535018박웅기.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <glut.h>
#include <gl.h>
#include <glu.h>

static int Day = 0, Time = 0;

GLboolean IsSolidSphere = false; // 행성이 솔리드 형태인지, 와이어 형태인지
GLboolean IsPerspective = false; // 평행 투상인지, 원근 투상인지에 대한 boolean타입

/* 모델뷰행렬과 투상행렬을 항등행렬로 초기화 하는 Init 작업 */
void Init() {
	glClearColor(0.0, 0.0, 0.0, 1.0); // 배경 색깔 우주니까 검정색으로 설정

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/* 가리워짐 현상을 하는 수행하는 함수 */
void CoveredPlanetFace() {
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
}

/* 태양계 구현부 함수 */
void DrawSolarSystem() {
	glColor3f(1.0, 0.3, 0.3); // 태양 색상
	glPushMatrix();	// 전역 좌표계 저장
					// 여태까지 작업 저장, 안전을 위한 행위 및 코드 상에서 수정사항이 있을 때,
					// 각각마다 건드리지 않기 위해 격격마다 push pop을 해서 번거롭지 않게 함. 
					// 앞으로 계속 이런식으로 push pop함 이렇게 안하고 절차지향적으로 행렬을 왔다갔다하면 불편함!
	{
		if (IsSolidSphere)
			glutSolidSphere(0.2, 20, 16); // 태양의 반지름, 원이나 구나 다각형의 모임이기 때문에, 두번째 세번째 인자가 필요함.
		else
			glutWireSphere(0.2, 20, 16); // 태양의 반지름, 세로, 가로 와이어 개수

		glPushMatrix(); // 태양 좌표계 저장
		{
			glRotated((GLfloat)Day, 0.0, 1.0, 0.0); // 10도 씩 이동함
			glTranslatef(0.7, 0.0, 0.0);
			glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // 5도 씩 이동
			glColor3f(0.5, 0.6, 0.7); // 지구 색상
			if (IsSolidSphere)
				glutSolidSphere(0.1, 10, 8);
			else
				glutWireSphere(0.1, 10, 8); // 지구의 반지름, 세로, 가로 와이어 개수

			glPushMatrix(); // 지구 좌표계 저장
			{
				glRotatef((GLfloat)Time, 0.0, 1.0, 0.0); // 5도 씩 이동
				glTranslatef(0.2, 0.0, 0.0);
				glColor3f(0.9, 0.8, 0.2); // 달 색상
				if (IsSolidSphere)
					glutSolidSphere(0.04, 10, 8);
				else
					glutWireSphere(0.04, 10, 8); // 달의 반지름, 세로, 가로 와이어 개수
			}
			glPopMatrix(); // 지구 좌표계 복원
		}
		glPopMatrix(); // 태양 좌표계 복원
	}
	glPopMatrix(); 	// 전역 좌표계 복원, 중요한 점은 push pop은 쌍으로 이루어져야 함. push만 계속하면 초반에는 잘되지만 나중에 문제생기겠지.
}

void MyDisplay() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	CoveredPlanetFace(); // 달이나 지구가 태양 뒤에 있을 때, 달이 지구 뒤에 있을 때 (배우진 않았지만 그냥 찾아서 함)

	glMatrixMode(GL_PROJECTION);
	glPushMatrix(); // 여태 초기 작업 저장
	{
		glLoadIdentity();

		/* 평행인지 원근인지 IsPerspective로 구분해서 적용하기 */
		if (IsPerspective) {
			gluPerspective(60, 1.0, 1.0, 50.0); // 각도 60(각도가 넓을 수록 변화 폭이 큼), 종횡 비, near, far
			gluLookAt(0.0, 0.0, 1.9, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0); // 시점 위치 z = 1.9 에서 바라보는 중.
		}
		else
			glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0); // 평행일 때의 가시부피 비율, 당연히 원근 효과 없음

		glMatrixMode(GL_MODELVIEW);

		glPushMatrix(); // 평행 원근 작업 저장
		{
			DrawSolarSystem(); // 솔라 시스템 그리는 함수 호출
		}
		glPopMatrix(); // 평행 원근 작업 복원

		glMatrixMode(GL_PROJECTION);
	}
	glPopMatrix(); // 저장했던 초기 작업 복원

	glFlush();

	glutSwapBuffers();
}

void MyKeyboard(unsigned char key, int x, int y) {
	switch (key) {
	case 'd':
		Day = (Day + 10) % 360; // 360도 회전을 위한 작업이다. Day가 360이면 원래 위치로 돌아감
		glutPostRedisplay(); // 바뀐 값을 새로이 디스플레이에 출력하는 함수
		break;
	case 't':
		Time = (Time + 5) % 360; // 이하 동문
		glutPostRedisplay();
		break;
	default:
		break;
	}
}

void MyMainMenu(int entryID) {
	if (entryID == 1)
		exit(0); // 정상 종료
}

void MySubPerspectiveMenu(int entryID) {
	if (entryID == 1)
		IsPerspective = false;
	else if (entryID == 2)
		IsPerspective = true;
	glutPostRedisplay();
}

void MySubRenderMenu(int entryID) {
	if (entryID == 1)
		IsSolidSphere = true;
	else if (entryID == 2)
		IsSolidSphere = false;
	glutPostRedisplay();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutCreateWindow("Solar System");

	GLint MySubPerspectiveMenuID = glutCreateMenu(MySubPerspectiveMenu); // 메뉴 콜백함수가 등록되고, 그 메뉴에 대한 아이디 값이 리턴됨.
	glutAddMenuEntry("Parallel", 1);
	glutAddMenuEntry("Perspective", 2); // 현메뉴에 메뉴 항목을 추가하는 작업 앞에 건 그냥 나타내는 작업이고, 두 번째 것이 value로서 해당하는 숫자인 것의 항목을 실행함.

	GLint MySubRenderMenuID = glutCreateMenu(MySubRenderMenu);
	glutAddMenuEntry("Solid Sphere", 1);
	glutAddMenuEntry("Wire Sphere", 2);

	GLint MyMainMenuID = glutCreateMenu(MyMainMenu);
	glutAddSubMenu("Change Perspective Shape", MySubPerspectiveMenuID); // 서브 메뉴를 추가하는 작업
	glutAddSubMenu("Change Rendering Shape", MySubRenderMenuID);
	glutAddMenuEntry("Exit", 1);

	glutAttachMenu(GLUT_RIGHT_BUTTON);

	Init();
	glutDisplayFunc(MyDisplay);
	glutKeyboardFunc(MyKeyboard);
	glutMainLoop();

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
