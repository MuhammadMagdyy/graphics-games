//  Includes
#include <stdio.h>
#include <math.h>
#include <random>
#include <string>
#include <GLUT/glut.h>
#include <stdlib.h>
//-----------------
#define SPACEBAR 32
void Anim(void);

/*
* glClear(GL_COLOR_BUFFER_BIT);

// spaceship
glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(103.0f, 95.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(125.0f, 95.0f, 0.0f);

	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(146.0f, 95.0f, 0.0f);
	glEnd();
	

	
	glBegin(GL_LINE_LOOP); // GL_LINE_STRIP, GL_LINE_LOOP
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(85.0f, 90.0f, 0.0f);
	glVertex3f(165.0f, 90.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(85.0f, 90.0f, 0.0f);
	glVertex3f(125.0f, 155.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(125.0f, 155.0f, 0.0f);
	glVertex3f(165.0f, 90.0f, 0.0f);


	glEnd();
	

	
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(90.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(160.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(125.0f, 150, 0.0f);
	glEnd();


// invader

	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(373.0f, 590.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(373.0f, 510.0f, 0.0f);

	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(551.0f, 590.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(551.0f, 510.0f, 0.0f);
	glEnd();


	glBegin(GL_QUAD_STRIP); // GL_QUAD_STRIP

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(375.0f, 600.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(550.0f, 600.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(375.0f, 500.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(550.0f, 500.0f, 0.0f);
	glEnd();


	glBegin(GL_LINE_LOOP); // GL_LINE_STRIP, GL_LINE_LOOP
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(375.0f, 600.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(375.0f, 510.0f, 0.0f);

	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(550.0f, 600.0f, 0.0f);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex3f(550.0f, 510.0f, 0.0f);
	glEnd();



// powerup

glBegin(GL_QUAD_STRIP); // GL_QUAD_STRIP
	glVertex3f(100.0f, 100.0f, 0.0f);
	glVertex3f(100.0f, 110.0f, 0.0f);
	glVertex3f(110.0f, 100.0f, 0.0f);
	glVertex3f(110.0f, 110.0f, 0.0f);
	glEnd();


// spaceship laser
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(90.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(100.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(95.0f, 110, 0.0f);
	glEnd();


// invader laser
glBegin(GL_QUAD_STRIP); // GL_QUAD_STRIP

	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(300.0f, 320.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(320.0f, 320.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(300.0f, 300.0f, 0.0f);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(320.0f, 300.0f, 0.0f);
	glEnd();

*/

float  invaderX = 0.9, fireX = invaderX, fireY = 1.8, playerX = 0, playerY = -1.7, invaderY = 1.8, laserX = 0, laserY = -3.0, powerX = -1, powerY = -0.5; // Changed: Player now starts at center bottom (playerY = -1.7) instead of middle
// Added: Array-based laser system for unlimited consecutive shots
float laserXArray[10] = {0};
float laserYArray[10];  // Initialize all to -3.0 below
bool isShootingArray[10] = {false};
int shotCounter = 0; // Counter to cycle through laser array
// Added: Array for multiple enemy bullets that fall simultaneously
float fireXArray[4] = {0}, fireYArray[4] = {1.8, 1.8, 1.8, 1.8};
bool fireActiveArray[4] = {false};
int enemyBulletIndex = 0; // Counter for which bullet slot to use next
int bulletFireDelay = 0; // Delay counter for spacing out bullet fires
// Added: Power-up timing system
int powerUpDisplayTimer = 0; // Counter for how long power-up has been visible
int powerUpRespawnDelay = 0; // Counter for delay before next power-up spawns
const int POWERUP_DISPLAY_TIME = 300; // Frames power-up stays visible (5 seconds at 60 FPS)
const int POWERUP_RESPAWN_TIME = 150; // Frames before power-up can spawn again
// Initialize all laser Y positions
const float LASER_INIT_Y = -3.0;
int invaderHealth = 20;
int totalInvaderHealth = invaderHealth;
int flagOut = 0;
int health = 3;
int flagOut1 = 0;
int flag = 0;
int powerUpFlag = 0;
int timer =0;
int fireTimer = 0; // Added: Timer for enemy firing frequency
int rand(), r;
// New globals for key tracking and shooting
bool keys[256] = {false}; // Array to track key states for continuous movement
bool isShooting = false; // Flag to control player shooting (only on key press)
bool powerUpActive = false; // Flag to control power-up visibility and spawning
bool gameRunning = true; // Added: Flag to control if game is running
std::string gameState = ""; // Added: String to display game over or win message

// Key handling functions for continuous movement
void keyDown(unsigned char key, int x, int y) {
    keys[key] = true;
    if (key == ' ') { // Spacebar for shooting
        // Changed: Continuous shooting - cycle through laser array
        if (!isShootingArray[shotCounter]) {
            laserYArray[shotCounter] = playerY + 0.5;
            laserXArray[shotCounter] = playerX;
            isShootingArray[shotCounter] = true;
            shotCounter = (shotCounter + 1) % 10; // Cycle to next laser
        }
    }
    // Added: ESC key to quit the game
    if (key == 27) { // 27 is ASCII for ESC
        exit(0);
    }
}
void keyUp(unsigned char key, int x, int y) {
    keys[key] = false;
}
void specialKeyDown(int key, int x, int y) {
    keys[key + 128] = true; // Offset special keys
}
void specialKeyUp(int key, int x, int y) {
    keys[key + 128] = false;
}
void init() 
{
	// Initialize all player laser Y positions to be off-screen
	for (int i = 0; i < 10; i++) {
		laserYArray[i] = LASER_INIT_Y;
	}
	glClearColor(1, 1, 1, 1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-2, 2, -2, 2, -2, 2);
	glMatrixMode(GL_MODELVIEW);

}
void fire() 
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireSphere(0.1, 25, 25);
}
void player()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireCone(0.3, 0.5, 25, 25);

}
void Invader()
{
	glColor3f(0.0f, 0.0f, 1.0f);
	glutSolidCube(1);
}
void laser() {
	glColor3f(0.0f, 1.0f, 0.0f);
	glutWireSphere(0.02, 25, 25);

}
void powerUp() 
{
	glColor3f(1.0f, 0.0f, 1.0f);
	glutSolidCube(0.1);
}

void spaceShipAfterPowerUp() 
{
	glColor3f(1.0f, 0.0f, 1.0f);
	glutWireCone(0.3, 0.5, 25, 25);
}


void invaderHealthbar_3() 
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
}
void invaderHealthbar_2()
{
	glColor3f(1.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
}
void invaderHealthbar_1()
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(0.5);
}

void playerHealthbar()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(0.05);
}
void end() 
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glutSolidCube(0.5);
}
void won()
{
	glColor3f(0.0f, 1.0f, 0.0f);
	glutSolidCube(0.5);
}

// Added: Function to draw text on screen
void drawText(const char* text, float x, float y) {
    glColor3f(1.0f, 1.0f, 1.0f); // White text
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display()
{
	// Changed: Set white background for normal gameplay
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Added: If game is not running, display game over or win message and stop updating
	if (!gameRunning) {
		// Changed: Set black background with red text
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glLoadIdentity();
		glColor3f(1.0f, 0.0f, 0.0f); // Red text
		glRasterPos2f(-0.3f, 0.0f);
		for (const char* c = gameState.c_str(); *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
		glutSwapBuffers();
		glutPostRedisplay();
		return;
	}

	// Update player position based on held keys for smooth movement
	// Changed: Reduced speed from 0.3f to 0.1f for normal movement
	if (keys['w'] || keys['W'] || keys[GLUT_KEY_UP + 128]) playerY += 0.1f;
	if (keys['s'] || keys['S'] || keys[GLUT_KEY_DOWN + 128]) playerY -= 0.1f;
	if (keys['a'] || keys['A'] || keys[GLUT_KEY_LEFT + 128]) playerX -= 0.1f;
	if (keys['d'] || keys['D'] || keys[GLUT_KEY_RIGHT + 128]) playerX += 0.1f;

	// Added: Clamp player position within borders (-1.8 to 1.8 to leave some margin)
	if (playerX < -1.8f) playerX = -1.8f;
	if (playerX > 1.8f) playerX = 1.8f;
	if (playerY < -1.8f) playerY = -1.8f;
	if (playerY > 1.8f) playerY = 1.8f;

	// when timer finishes, start new powerup
	//printf("timer = %i\n", timer);
	/*while (timer != 0)
	{
		timer--;
	}*/
	if (timer == 0)
		powerUpFlag = 0;
	
	// Changed: Added power-up timing logic
	// Increment respawn delay counter
	if (powerUpRespawnDelay > 0) {
		powerUpRespawnDelay--;
	}
	
	// If power-up is active, increment display timer
	if (powerUpActive) {
		powerUpDisplayTimer++;
		// Hide power-up after display time expires
		if (powerUpDisplayTimer > POWERUP_DISPLAY_TIME) {
			powerUpActive = false;
			powerUpDisplayTimer = 0;
			powerUpRespawnDelay = POWERUP_RESPAWN_TIME; // Start respawn delay
		}
	}
	
	// Old power-up spawning: checked every frame with low probability, causing flashing
	// Changed: spawn immediately after respawn delay is complete at a new random position
	if (powerUpFlag == 0 && !powerUpActive && powerUpRespawnDelay == 0) {
		// Pick a new random position for the power-up
		int pos = rand() % 4;
		if (pos == 0) { powerX = -1; powerY = -0.5; }
		else if (pos == 1) { powerX = 0.4; powerY = -1.6; }
		else if (pos == 2) { powerX = 1.5; powerY = 1.3; }
		else { powerX = -0.5; powerY = 1.8; }
		// Spawn power-up at new position
		powerUpActive = true;
		powerUpDisplayTimer = 0; // Reset display timer
	}
	// Draw power-up only if active
	if (powerUpActive) {
		glPushMatrix();
		glTranslatef(powerX, powerY, 0);
		powerUp();
		glPopMatrix();
	}
	

	
	/*printf("fireX=%f\n", fireX);
	printf("fireY=%f\n", fireY);
	printf("playerX=%f\n", playerX);
	printf("playerY=%f\n", playerY);
	printf("invaderX=%f\n", invaderX);
	printf("invaderY=%f\n", invaderY);
	printf("laserX=%f\n", laserX);
	printf("laserY=%f\n", laserY);*/

	/*
	// show invaderhealth
	glPushMatrix();
	glTranslatef(-1.7, 1.8, 0);
	printf("health= %i\n", health);
	glPopMatrix();


	// show health bar
	glPushMatrix();
	glTranslatef(1.8, -1.8 , 0);
	printf("invaderHealth= %i\n", invaderHealth);
	glPopMatrix();*/

	

	// Added: Check collision between player and enemy (can't touch, only shoot)
	if (playerX > invaderX - 0.6 && playerX < invaderX + 0.6 && playerY > invaderY - 0.3 && playerY < invaderY + 0.3) {
		// Player touched enemy - lose health
		health--;
		if (health == 0) {
			gameState = "Game Over";
			gameRunning = false;
		}
		// Push player back
		playerY -= 0.3;
	}

	// Changed: Multiple enemy bullets check collision with player
	for (int i = 0; i < 4; i++) {
		if (fireActiveArray[i] && fireYArray[i] <= playerY + 0.3 && fireYArray[i] >= playerY - 0.3 && fireXArray[i] > playerX - 0.3 && fireXArray[i] < playerX + 0.3) {
			if (powerUpFlag == 0) {
				health--; // Decrease health when hit, unless powered up
			}
			fireActiveArray[i] = false; // Remove bullet after hit
			fireYArray[i] = 1.8;

			if (health == 0) {
				// Changed: Show "Game Over" text and stop the game
				gameState = "Game Over";
				gameRunning = false;
				flagOut = 1;
				flagOut1 = 1;
			}
			break; // Stop checking other bullets after collision
		}
	}
	// Changed: Multiple enemy bullets system - each bullet falls independently
	if (flagOut == 0) {
		for (int i = 0; i < 4; i++) {
			if (fireActiveArray[i]) {
				fireYArray[i] -= 0.005; // Changed: Increased speed from 0.003 to 0.005 for faster bullets
			}
			if (fireYArray[i] < -2) {
				fireActiveArray[i] = false;
				fireYArray[i] = 1.8;
			}
		}
	}
	// Changed: Fire bullets consecutively with time gaps instead of all at once
	fireTimer++;
	// Fire one bullet every 100 frames from the next available slot
	if (fireTimer > 100) {
		// Fire from the next slot only (not all at once)
		if (!fireActiveArray[enemyBulletIndex]) {
			fireYArray[enemyBulletIndex] = 1.8;
			fireXArray[enemyBulletIndex] = invaderX;
			fireActiveArray[enemyBulletIndex] = true;
			enemyBulletIndex = (enemyBulletIndex + 1) % 4; // Cycle to next slot
		}
		fireTimer = 0;
	}



	// Changed: Check collision for all player lasers with enemy
	for (int i = 0; i < 10; i++) {
		if (isShootingArray[i] && laserYArray[i] > invaderY && laserXArray[i] > invaderX - 0.5 && laserXArray[i] < invaderX + 0.5) {
			invaderHealth -= 5;
			isShootingArray[i] = false; // Remove laser after hit
			laserYArray[i] = LASER_INIT_Y;
			if (invaderHealth <= 0) {
				gameState = "You Won";
				gameRunning = false;
				flagOut1 = 1;
				flagOut = 1;
			}
			break; // Only count one hit per frame
		}
	}

	// Changed: Move all active player lasers
	for (int i = 0; i < 10; i++) {
		if (isShootingArray[i]) {
			laserYArray[i] += 0.025; // Changed: Increased speed from 0.02 to 0.025 for faster shooting
		}
		if (laserYArray[i] > 2) {
			isShootingArray[i] = false; // Reset shooting flag
			laserYArray[i] = LASER_INIT_Y; // Reset below screen
		}
	}

	// To keep the invader moving left and right
	// Increased speed for more dynamic gameplay
	// Changed: Increased speed from 0.003 to 0.005 for even faster enemy movement
	if (flag == 0)
	{
		invaderX += 0.005;
		if (invaderX > 2)
			flag = 1;
	}
	if (flag == 1)
	{
		invaderX -= 0.005;
		if (invaderX < -2)
			flag = 0;
	}

	// incase of touching the powerup 
	if (powerX > playerX - 0.1 && powerX < playerX + 0.1 && powerY > playerY - 0.4 && powerY < playerY + 0.4)
	{
		powerUpFlag = 1;
		timer = 200; // Increased timer for longer power-up duration
		powerUpActive = false; // Hide power-up after collection
		powerUpDisplayTimer = 0; // Reset display timer
		powerUpRespawnDelay = POWERUP_RESPAWN_TIME; // Set respawn delay so it doesn't immediately reappear
	}
	
	// Changed: Draw all active enemy bullets
	for (int i = 0; i < 4; i++) {
		if (fireActiveArray[i]) {
			glPushMatrix();
			glTranslatef(fireXArray[i], fireYArray[i], 0);
			fire();
			glPopMatrix();
		}
	}

	// Changed: Draw all active player lasers
	for (int i = 0; i < 10; i++) {
		if (isShootingArray[i]) {
			glPushMatrix();
			glTranslatef(laserXArray[i], laserYArray[i], 0);
			laser();
			glPopMatrix();
		}
	}

	glPushMatrix();
	glTranslatef(playerX, playerY, 0);
	glRotatef(270, 1, 0, 0);
	if (powerUpFlag == 1)
	{
		spaceShipAfterPowerUp();
		timer--;
		
	}
	else 
	{
		player();
	}
	glPopMatrix();

	for (int i = 0; i < 10000; i++);


    glPushMatrix();
    glTranslatef(invaderX , invaderY , 0);
    glScalef(1, 0.5, 1);
	Invader();
	glPopMatrix();


	

	// error when it reaches zero
	//printf("invaderHealth=%i\n", invaderHealth);
	//printf("totalInvaderHealth=%i\n", totalInvaderHealth);

	double percentage =  ((double)invaderHealth / (double) totalInvaderHealth ) * 100;
	//	printf("percentage= %f\n", percentage);


	// Invader's health bar
	int per = (int)percentage;
//	printf("per = %i\n", per);
	if (per >= 40 && per < 70) {
		glPushMatrix();
		glTranslatef(invaderX, invaderY - 0.3, 0);
		glScalef(1.5, 0.08, 1);
		invaderHealthbar_2();
		glPopMatrix();
	}
	
	if (per <= 100 && per >= 70)
	{
		glPushMatrix();
		glTranslatef(invaderX, invaderY - 0.3, 0);
		glScalef(2, 0.08, 1);
		invaderHealthbar_3();
		glPopMatrix();
	}

	if (per>= 0 && per <40) 
	{
		glPushMatrix();
		glTranslatef(invaderX, invaderY - 0.3, 0);
		glScalef(0.5, 0.08, 1);
		invaderHealthbar_1();
		glPopMatrix();
	}




	// Player's health bar
	if (health == 3)
	{
		glPushMatrix();
		glTranslatef(-1.9, 1.2, 0);
		//glScalef(0.5, 0.08, 1);
		playerHealthbar();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.8, 1.2, 0);
		//glScalef(0.5, 0.08, 1);
		playerHealthbar();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.7, 1.2, 0);
		//glScalef(0.5, 0.08, 1);
		playerHealthbar();
		glPopMatrix();

	}
	if (health == 2)
	{
		glPushMatrix();
		glTranslatef(-1.9, 1.2, 0);
		//glScalef(0.5, 0.08, 1);
		playerHealthbar();
		glPopMatrix();

		glPushMatrix();
		glTranslatef(-1.8, 1.2, 0);
		//glScalef(0.5, 0.08, 1);
		playerHealthbar();
		glPopMatrix();

	}
	if (health == 1)
	{
		glPushMatrix();
		glTranslatef(-1.9, 1.2, 0);
		//glScalef(0.5, 0.08, 1);
		playerHealthbar();
		glPopMatrix();
	}
	


	glutSwapBuffers();
	glutPostRedisplay();
}

void controls(int key, int x, int y)
{
	if (key == GLUT_KEY_LEFT)
	{
		playerX -= 0.1;
	}
	if (key == GLUT_KEY_RIGHT)
	{
		playerX += 0.1;
	}
	if (key == GLUT_KEY_UP)
	{
		playerY += 0.1;
	}
	if (key == GLUT_KEY_DOWN)
	{
		playerY -= 0.1;
	}
	
}


int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Space Invaders");
	init();
	glutDisplayFunc(display);
	// Old: glutSpecialFunc(controls); // Only handled special keys on press
	// New: Handle key presses and releases for continuous movement
	glutKeyboardFunc(keyDown);
	glutKeyboardUpFunc(keyUp);
	glutSpecialFunc(specialKeyDown);
	glutSpecialUpFunc(specialKeyUp);
	glEnable(GL_DEPTH_TEST);
	glutMainLoop();
	return 0;

}

