#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <glut.h>
#include <string.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)

float playerx, playerz = 0;
float ballx = 0.5;
float ballz = 0.5;
int goals = 0;
class Vector3f {
public:
	float x, y, z;

	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	Vector3f operator+(Vector3f& v) {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	Vector3f operator-(Vector3f& v) {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	Vector3f operator*(float n) {
		return Vector3f(x * n, y * n, z * n);
	}

	Vector3f operator/(float n) {
		return Vector3f(x / n, y / n, z / n);
	}

	Vector3f unit() {
		return *this / sqrt(x * x + y * y + z * z);
	}

	Vector3f cross(Vector3f v) {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

class Camera {
public:
	Vector3f eye, center, up;

	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;


void drawGround(double thickness) {

	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glColor3f(0.2f, 1.0f, 0.2f);
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

void drawLeg(double thick, double len) {

	glPushMatrix();
	glTranslated(0, len / 2, 0);
	glScaled(thick, len, thick);
	glutSolidCube(1.0);

	glPopMatrix();
}

void flags() {
	/*                   Flags                   */

/*                      1st flag              */
	glPushMatrix();
	glTranslated(0.045, 0.4, 0.41);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(0.4f, 0.7f, 0.3f);
	drawLeg(0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.045, 0.43, 0.41);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(250.0f, 250.0f, 250.0f);
	drawLeg(0.1, 0.1);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.045, 0.46, 0.41);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(1.0f, 0.2f, 0.2f);
	drawLeg(0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.0, 0.4);
	glColor3f(250.0f, 250.0f, 250.0f);
	drawLeg(0.01, 0.4);
	glPopMatrix();

	////////////////////////////////////////

	/*              2nd flag        */
	glPushMatrix();
	glTranslated(0.045, 0.4, 0.51);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(0.9f, 0.9f, 0.0f);

	drawLeg(0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.045, 0.43, 0.51);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(0.9f, 0.2f, 0.3f);
	drawLeg(0.1, 0.1);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.045, 0.46, 0.51);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawLeg(0.1, 0.1);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0, 0.0, 0.5);
	glColor3f(250.0f, 250.0f, 250.0f);
	drawLeg(0.01, 0.4);
	glPopMatrix();
	////////////////////////////////////////////

	/*                  3rd flag              */
	glPushMatrix();
	glTranslated(0.045, 0.4, 0.61);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(1.0f, 0.2f, 0.3f);
	drawLeg(0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.045, 0.43, 0.61);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(250.0f, 250.0f, 250.0f);
	drawLeg(0.1, 0.1);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.045, 0.46, 0.61);
	glScaled(0.9, 0.3, 0.01);
	glColor3f(1.0f, 0.2f, 0.3f);
	drawLeg(0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.0, 0.6);
	glColor3f(250.0f, 250.0f, 250.0f);
	drawLeg(0.01, 0.4);
	glPopMatrix();

	//////////////////////////////////////////
}
void corners() {
	/*        Top left corner          */

	glPushMatrix();
	glTranslated(0.045, 0.2, 0.01);
	glScaled(0.9, 0.4, 0.01);
	glColor3f(1.0f, 1.0f, 0.4f);
	drawLeg(0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0, 0.0, 0.0);
	glColor3f(250.0f, 250.0f, 250.0f);
	drawLeg(0.01, 0.2);
	glPopMatrix();


	/*                                 */


	/*        Top right corner          */

	glPushMatrix();
	glTranslated(1.035, 0.2, 0.01);
	glScaled(0.9, 0.4, 0.01);
	glColor3f(1.0f, 1.0f, 0.4f);
	drawLeg(0.1, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.995, 0.0, 0);
	glColor3f(250.0f, 250.0f, 250.0f);
	drawLeg(0.01, 0.2);
	glPopMatrix();


	////////////////////////////////////////////////////////////////
}
void net() {
	/////////////////////////////////////
	/*                net                   */
	glPushMatrix();
	glTranslated(0.25, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawLeg(0.01, 0.1);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.8, 0.0, 0.0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawLeg(0.01, 0.1);
	glPopMatrix();


	glPushMatrix();
	glTranslated(0.8, 0.0, 0.2);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawLeg(0.01, 0.3);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.25, 0.0, 0.2);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawLeg(0.01, 0.3);
	glPopMatrix();


	//glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslated(0.525, 0.2, 0.1);
	glRotated(-45, 1, 0, 0);
	glScaled(2.75, 0.09, 1.3);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutSolidCube(0.2);
	glPopMatrix();

	/////////////////////////////////////////////////////
}
void banners() {
	/*  3 Ad banners         */
// 1st banner
	glPushMatrix();
	glTranslated(1.05, -0.1, 0.5);
	glScaled(0.2, 1.0, 0.9);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawLeg(0.4, 0.2);
	glPopMatrix();

	// 2nd banner
	glPushMatrix();
	glTranslated(1.05, 0.0, 0.5);
	glRotated(90, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 1.0, 0.9);
	glTranslated(-2.8, -0.1, 0.9);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawLeg(0.4, 0.2);
	glPopMatrix();

	// 3rd banner
	glPushMatrix();
	glTranslated(1.05, 0.0, 0.5);
	glRotated(90, 0, 0, 1);
	glRotated(-90, 1, 0, 0);
	glRotated(90, 0, 0, 1);
	glScaled(0.2, 1.0, 0.9);
	glTranslated(-2.8, -0.1, 0.3);
	glColor3f(0.0f, 0.0f, 0.0f);
	drawLeg(0.4, 0.2);
	glPopMatrix();

	///////////////////////////////////////////////
}

void player() {
	///////////////////////////////////////////////

	/*               player                */
	
	//face
	glPushMatrix();
	glTranslated(0.5+playerx, 0.305, 0.7+playerz);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidSphere(0.03, 15, 15);
	glPopMatrix();

	//body
	glPushMatrix();
	glTranslated(0.5 + playerx, 0.2, 0.7 + playerz);
	glScaled(0.7, 1.3, 0.6);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(0.1);
	glPopMatrix();

	//legs
	glPushMatrix();
	glTranslated(0.525 + playerx, 0, 0.7 + playerz);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.475 + playerx, 0, 0.7 + playerz);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.2);
	glPopMatrix();

	//hands
	glPushMatrix();
	glTranslated(0.59 + playerx, 0.17, 0.7 + playerz);
	glRotated(30, 0, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.106);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.41 + playerx, 0.17, 0.7 + playerz);
	glRotated(-30, 0, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.106);
	glPopMatrix();

}
void ball() {
	//ball
	//right leg translation (0.525 + playerx, 0, 0.7 + playerz)


	if ((ballz)<= (playerz + 0.7) && (playerz + 0.7) <= (ballz + 0.01) && (ballx - 0.02) < (0.59 + playerx) < (ballx + 0.06))
	{
		ballz -= 0.05;
		if (ballz <= -0.4)
			goals += 1;
			
	}
		
		
	glPushMatrix();
	glTranslated(ballx, 0.045, ballz);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(0.025, 15, 15);
	glPopMatrix();
	//////////////////////////////////////
}

void cup() {

	glPushMatrix();
	glTranslated(0.1, 0.27, 0.5);
	glColor3f(1.0f, 0.9f, 0.1f);
	glutSolidSphere(0.03, 15, 15);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.1, 0, 0.5);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawLeg(0.1, 0.2);
	glPopMatrix();

	glPushMatrix();
	glTranslated(0.1, 0.21, 0.5);
	glColor3f(1.0f, 0.9f, 0.1f);
	drawLeg(0.05, 0.05);
	glPopMatrix();

}
void setupLights() {
	GLfloat ambient[] = { 0.7f, 0.7f, 0.7, 1.0f };
	GLfloat diffuse[] = { 0.6f, 0.6f, 0.6, 1.0f };
	GLfloat specular[] = { 1.0f, 1.0f, 1.0, 1.0f };
	GLfloat shininess[] = { 50 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shininess);

	GLfloat lightIntensity[] = { 0.7f, 0.7f, 1, 1.0f };
	GLfloat lightPosition[] = { -7.0f, 6.0f, 3.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, lightIntensity);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);
}
void setupCamera() {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, 640 / 480, 0.001, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	camera.look();
}

void print(int x, int y, char* string)
{
	int len, i;

	//set the position of the text in the window using the x and y coordinates
	glRasterPos2f(x, y);

	//get the length of the string to display
	len = (int)strlen(string);

	//loop to display character by character
	for (i = 0; i < len; i++)
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	}
}


void Display() {
	setupCamera();
	setupLights();


	//printf("playerz = % f\n", playerz);
	//printf("playerx = % f\n", playerx);

	//printf("playerz = % f\n", playerz);
	//printf("playerz = % f\n", playerz);


	/*printf("camera.eye.x  = % f\n", camera.eye.x);
	printf("camera.eye.y  = % f\n", camera.eye.y);
	printf("camera.eye.z  = % f\n", camera.eye.z);

	printf("camera.center.x = % f\n", camera.center.x);
	printf("camera.center.y = % f\n", camera.center.y);
	printf("camera.center.z = % f\n", camera.center.z);

	printf("camera.up.x = % f\n", camera.up.x);
	printf("camera.up.y = % f\n", camera.up.y);
	*/
	printf("Goal!!!!!!!!!!!\n");


	if (goals == 1) {
		glColor3f(1, 0, 0);
		char* p0s[20];
		sprintf((char*)p0s, "Goals: %d", goals);
		print(500, 300, (char*)p0s);
	}


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//cup
	cup();

	//Ground
	drawGround(0.02);
	//net
	net();

	// football
	ball();
	//player
	player();

	//banners
	banners();
	//flags
	flags();
	//corners
	corners();

	cup();

	

	


	glFlush();
}

void Keyboard(unsigned char key, int x, int y) {
	float d = 0.01;

	switch (key) {
	case 'w':
		camera.moveY(d);
		break;
	case 's':
		camera.moveY(-d);
		break;
	case 'a':
		camera.moveX(d);
		break;
	case 'd':
		camera.moveX(-d);
		break;
	case 'q':
		camera.moveZ(d);
		break;
	case 'e':
		camera.moveZ(-d);
		break;
	case 'f':
		if (playerz <= -0.5)
		{
			break;
		}
			playerz -= 0.01;
		break;
	case 'b':
		if (playerz >= 0.3)
		{
			break;
		}
			playerz += 0.01;
			break;
		
	case 'r':
		if (playerx <= -0.5)
		{
			break;
		}
			playerx -= 0.01;
			break;
	
	case 'l':
		if (playerx >= 0.48)
		{
			break;
		}	
		playerx += 0.01;
		break;
		
	case '1':
		camera.eye.x  = 0.676501;
		camera.eye.y = 1.608359;
		camera.eye.z = 0.676501;
		camera.center.x = 0.571370;
		camera.center.y = 0.619473;
		camera.center.z = 0.571370;
		camera.up.x = -0.699248;
		camera.up.y = 0.148678;
		camera.up.z = -0.699248;
		break;

	case '3':
		camera.eye.x = 0.502748;
		camera.eye.y = 0.437678;
		camera.eye.z = 1.862529;
		camera.center.x = 0.498378;
		camera.center.y = 0.260331;
		camera.center.z = 0.878390;
		camera.up.x = -0.016011;
		camera.up.y = 0.984034;
		camera.up.z = -0.177258;
		break;

	case '2':
		camera.eye.x = 1.948013;
		camera.eye.y = 0.398301;
		camera.eye.z = 0.803821;
		camera.center.x = 0.973151;
		camera.center.y = 0.367399;
		camera.center.z = 0.583164;
		camera.up.x = -0.031784;
		camera.up.y = 0.999495;
		camera.up.z = 0.000445;
		break;
		
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();
}
void Special(int key, int x, int y) {
	float a = 1.0;

	switch (key) {
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();
}

void main(int argc, char** argv, char** argr) {
	glutInit(&argc, argv);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(50, 50);

	glutCreateWindow("Lab 5");
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutSpecialFunc(Special);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glClearColor(0.1f, 0.9f, 1.0f, 0.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);




	glShadeModel(GL_SMOOTH);

	glutMainLoop();

	if (goals == 1) {
		glutInit(&argc, argr);

		glutInitWindowSize(1000, 600);

		glutCreateWindow("OpenGL - 2D Template");
		glutDisplayFunc(Display);
		glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		gluOrtho2D(0.0, 1000, 0.0, 600);

		glutMainLoop();
	}
}
