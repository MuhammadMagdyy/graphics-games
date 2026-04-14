// ========================================
// 3D OpenGL Soccer Game
// ========================================
// This program creates an interactive 3D soccer field with a player
// that can be controlled to kick a ball into a goal using OpenGL and GLUT

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLUT/glut.h>
#include <string.h>

#define GLUT_KEY_ESCAPE 27
#define DEG2RAD(a) (a * 0.0174532925)  // Macro to convert degrees to radians

// Global variables for player and ball positions
float playerx, playerz = 0;  // Player X and Z coordinates (Y is fixed height)
float ballx = 0.5;           // Ball X position
float ballz = 0.5;           // Ball Z position
int goals = 0;               // Counter for goals scored
bool goalScored = false;     // Flag to track if goal message was already printed
bool showGoalScreen = false; // Flag to show goal celebration screen
bool ballKicked = false;     // Flag to track if ball has been kicked

// ========================================
// Vector3f Class: 3D Vector mathematical operations
// ========================================
class Vector3f {
public:
	float x, y, z;  // The three components of the vector

	// Constructor: Initializes vector with x, y, z values (default: 0,0,0)
	Vector3f(float _x = 0.0f, float _y = 0.0f, float _z = 0.0f) {
		x = _x;
		y = _y;
		z = _z;
	}

	// Vector addition: returns a new vector that is the sum of two vectors
	Vector3f operator+(const Vector3f& v) const {
		return Vector3f(x + v.x, y + v.y, z + v.z);
	}

	// Vector subtraction: returns a new vector that is the difference
	Vector3f operator-(const Vector3f& v) const {
		return Vector3f(x - v.x, y - v.y, z - v.z);
	}

	// Scalar multiplication: scales vector by multiplying each component by n
	Vector3f operator*(float n) const {
		return Vector3f(x * n, y * n, z * n);
	}

	// Scalar division: divides each component by n
	Vector3f operator/(float n) const {
		return Vector3f(x / n, y / n, z / n);
	}

	// Returns unit vector (normalized): vector with length 1 in same direction
	Vector3f unit() const {
		return *this / sqrt(x * x + y * y + z * z);
	}

	// Cross product: returns vector perpendicular to both this and v
	Vector3f cross(const Vector3f& v) const {
		return Vector3f(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}
};

// ========================================
// Camera Class: Manages 3D view and perspective
// ========================================
class Camera {
public:
	Vector3f eye;     // Camera position in 3D space
	Vector3f center;  // Point the camera is looking at
	Vector3f up;      // Vector pointing "up" from camera's perspective

	// Constructor: Sets camera position (eye), look-at point (center), and up direction
	Camera(float eyeX = 1.0f, float eyeY = 1.0f, float eyeZ = 1.0f, 
	       float centerX = 0.0f, float centerY = 0.0f, float centerZ = 0.0f, 
	       float upX = 0.0f, float upY = 1.0f, float upZ = 0.0f) {
		eye = Vector3f(eyeX, eyeY, eyeZ);
		center = Vector3f(centerX, centerY, centerZ);
		up = Vector3f(upX, upY, upZ);
	}

	// Move camera left/right along its local X axis
	void moveX(float d) {
		Vector3f right = up.cross(center - eye).unit();
		eye = eye + right * d;
		center = center + right * d;
	}

	// Move camera up/down along its local Y axis
	void moveY(float d) {
		eye = eye + up.unit() * d;
		center = center + up.unit() * d;
	}

	// Move camera forward/backward along its viewing direction
	void moveZ(float d) {
		Vector3f view = (center - eye).unit();
		eye = eye + view * d;
		center = center + view * d;
	}

	// Rotate camera up/down (around X axis)
	void rotateX(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + up * sin(DEG2RAD(a));
		up = view.cross(right);
		center = eye + view;
	}

	// Rotate camera left/right (around Y axis)
	void rotateY(float a) {
		Vector3f view = (center - eye).unit();
		Vector3f right = up.cross(view).unit();
		view = view * cos(DEG2RAD(a)) + right * sin(DEG2RAD(a));
		right = view.cross(up);
		center = eye + view;
	}

	// Apply camera transformation to OpenGL view
	void look() {
		gluLookAt(
			eye.x, eye.y, eye.z,
			center.x, center.y, center.z,
			up.x, up.y, up.z
		);
	}
};

Camera camera;

// ========================================
// DRAWING FUNCTIONS
// ========================================

// Draws the soccer field ground with green color
void drawGround(double thickness) {

	glPushMatrix();
	glTranslated(0.5, 0.5 * thickness, 0.5);
	glColor3f(0.2f, 1.0f, 0.2f);  // Green color
	glScaled(1.0, thickness, 1.0);
	glutSolidCube(1);
	glPopMatrix();
}

// Helper function: Draws a rectangular leg/cylinder for various objects
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
	// Draws the player character (blue humanoid figure) controlled by user
	// The player position is determined by playerx and playerz global variables
	
	// Head
	glPushMatrix();
	glTranslated(0.5+playerx, 0.305, 0.7+playerz);
	glColor3f(0.0f, 0.0f, 1.0f);  // Blue color
	glutSolidSphere(0.03, 15, 15);  // Draw sphere for head
	glPopMatrix();

	// Body
	glPushMatrix();
	glTranslated(0.5 + playerx, 0.2, 0.7 + playerz);
	glScaled(0.7, 1.3, 0.6);
	glColor3f(0.0f, 0.0f, 1.0f);  // Blue body
	glutSolidCube(0.1);
	glPopMatrix();

	// Left leg
	glPushMatrix();
	glTranslated(0.525 + playerx, 0, 0.7 + playerz);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.2);
	glPopMatrix();

	// Right leg
	glPushMatrix();
	glTranslated(0.475 + playerx, 0, 0.7 + playerz);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.2);
	glPopMatrix();

	// Right arm (raised at angle)
	glPushMatrix();
	glTranslated(0.59 + playerx, 0.17, 0.7 + playerz);
	glRotated(30, 0, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.106);
	glPopMatrix();

	// Left arm (raised at angle)
	glPushMatrix();
	glTranslated(0.41 + playerx, 0.17, 0.7 + playerz);
	glRotated(-30, 0, 0, 1);
	glColor3f(0.0f, 0.0f, 1.0f);
	drawLeg(0.01, 0.106);
	glPopMatrix();

}
void ball() {
	// Draws the soccer ball and handles collision detection with player
	
	// CHECK FOR COLLISION: If player gets close enough to the ball,
	// the ball gets kicked forward (negative Z direction)
	// Calculate distance from player's position to ball
	float playerCenterX = 0.5 + playerx;
	float playerCenterZ = 0.7 + playerz;
	
	// Distance from player to ball (simplified 2D distance)
	float distX = ballx - playerCenterX;
	float distZ = ballz - playerCenterZ;
	float distance = sqrt(distX * distX + distZ * distZ);
	
	// If player is within 0.1 units of the ball and ball hasn't been kicked yet, kick it
	if (distance < 0.1 && !ballKicked) {
		ballKicked = true;  // Set flag so ball moves a small distance
		printf("BALL KICKED! Distance: %.3f\n", distance);  // Debug output
	}
	
	// If ball has been kicked, move it a small distance toward goal, then reset
	if (ballKicked) {
		ballz -= 0.05;  // Move ball a small distance toward goal
		ballKicked = false;  // Reset flag so player must get close again
		printf("Ball moved: ballz = %.3f\n", ballz);  // Debug output
		
		if (ballz <= 0.0 && !goalScored) {  // If ball reaches goal area and goal not already scored
			goals += 1;  // Increment goal counter
			goalScored = true;  // Set flag so we don't score again
			showGoalScreen = true;  // Show goal celebration screen
			printf("GOAL SCORED! Total goals: %d, showGoalScreen: %d\n", goals, showGoalScreen);
		}
	}
		
	// Draw the ball as a black sphere
	glPushMatrix();
	glTranslated(ballx, 0.045, ballz);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(0.025, 15, 15);
	glPopMatrix();
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


void exitTimer(int value) {
	exit(0);
}

void Display() {
	// If showing goal celebration screen
	if (showGoalScreen) {
		printf("DISPLAYING GOAL SCREEN!\n");  // Debug output
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		// Set up 2D orthographic projection for text
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		gluOrtho2D(0.0, 1000, 0.0, 600);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		// Disable depth testing for 2D text
		glDisable(GL_DEPTH_TEST);
		
		// Set color to gold/yellow for celebration
		glColor3f(1.0f, 1.0f, 0.0f);
		
		// Display "GOALLLLLLLLLL!" in large text
		glRasterPos2f(200, 350);
		char* goalText = "GOALLLLLLLLLL!";
		for (int i = 0; goalText[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, goalText[i]);
		}
		
		// Display goal count
		glRasterPos2f(400, 250);
		char goalCount[50];
		sprintf(goalCount, "Total Goals: %d", goals);
		for (int i = 0; goalCount[i] != '\0'; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, goalCount[i]);
		}
		
		glFlush();  // Use glFlush() for single buffer mode
		
		// Set a timer to exit after 2 seconds
		glutTimerFunc(2000, exitTimer, 0);
		
		return;
	}

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
	// Goal scoring is now handled in ball() function with showGoalScreen flag


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
	// Handles keyboard input for camera and player movement
	float d = 0.01;  // Movement increment

	switch (key) {
	// Camera movement (up/down)
	case 'w':
		camera.moveY(d);  // Move camera up
		break;
	case 's':
		camera.moveY(-d);  // Move camera down
		break;
	// Camera movement (left/right)
	case 'a':
		camera.moveX(d);  // Move camera left
		break;
	case 'd':
		camera.moveX(-d);  // Move camera right
		break;
	// Camera movement (forward/backward)
	case 'q':
		camera.moveZ(d);  // Move camera forward
		break;
	case 'e':
		camera.moveZ(-d);  // Move camera backward
		break;
	
	// PLAYER MOVEMENT CONTROLS
	// Player forward (toward ball/goal - decrease Z toward goal)
	case 'f':
		if (playerz <= -0.7) {  // Boundary check (don't go past goal)
			break;
		}
		playerz -= 0.01;  // Move player forward (decrease Z toward ball/goal)
		break;
	// Player backward (away from goal - increase Z)
	case 'b':
		if (playerz >= 0.7) {  // Boundary check (back boundary)
			break;
		}
		playerz += 0.01;  // Move player backward (increase Z away from goal)
		break;
	
	// Player left (reduce X coordinate)
	case 'r':
		if (playerx <= -0.5) {  // Boundary check
			break;
		}
		playerx -= 0.01;
		break;
	
	// Player right (increase X coordinate)
	case 'l':
		if (playerx >= 0.48) {  // Boundary check
			break;
		}	
		playerx += 0.01;
		break;
	
	// PRESET CAMERA ANGLES - Press 1, 2, or 3 to switch views
	case '1':
		// View 1: Top-left corner view
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
		// View 3: Side view (right side)
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
		// View 2: Front view (goal view)
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
	
	// Exit program
	case GLUT_KEY_ESCAPE:
		exit(EXIT_SUCCESS);
	}

	glutPostRedisplay();  // Refresh display after input
}
void Special(int key, int x, int y) {
	// Handles special keys (arrow keys) for camera rotation
	float a = 1.0;  // Rotation angle in degrees

	switch (key) {
	// Rotate camera up
	case GLUT_KEY_UP:
		camera.rotateX(a);
		break;
	// Rotate camera down
	case GLUT_KEY_DOWN:
		camera.rotateX(-a);
		break;
	// Rotate camera left
	case GLUT_KEY_LEFT:
		camera.rotateY(a);
		break;
	// Rotate camera right
	case GLUT_KEY_RIGHT:
		camera.rotateY(-a);
		break;
	}

	glutPostRedisplay();  // Refresh display
}

// ========================================
// MAIN FUNCTION: Initializes OpenGL/GLUT and starts the game
// ========================================
int main(int argc, char** argv) {
	// Initialize GLUT with command line arguments
	glutInit(&argc, argv);

	// Create window with dimensions 640x480 pixels
	glutInitWindowSize(640, 480);
	// Position window on screen (50, 50)
	glutInitWindowPosition(50, 50);

	// Create the window with title "Lab 5"
	glutCreateWindow("Lab 5");
	// Set the function to call whenever window needs to be redrawn
	glutDisplayFunc(Display);
	// Set the function to handle keyboard input
	glutKeyboardFunc(Keyboard);
	// Set the function to handle special keys (arrows, etc)
	glutSpecialFunc(Special);

	// Set up display mode: single buffer, RGB colors, depth buffer
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	// Set background color to light blue (sky color)
	glClearColor(0.1f, 0.9f, 1.0f, 0.0f);

	// Enable 3D rendering features
	glEnable(GL_DEPTH_TEST);    // Enable depth testing for proper 3D rendering
	glEnable(GL_LIGHTING);      // Enable lighting calculations
	glEnable(GL_LIGHT0);        // Enable light source 0
	glEnable(GL_NORMALIZE);     // Auto-normalize normal vectors
	glEnable(GL_COLOR_MATERIAL); // Allow colors to override material colors

	// Use smooth shading (interpolates colors across faces)
	glShadeModel(GL_SMOOTH);

	// Start the event loop
	glutMainLoop();

	return 0;  // Return success code
}
