#include<iostream>
#include<GL/glut.h>
#include<math.h>
#include<cstdio>
#include<cstdlib>
#define PI 3.14
#include "imageloader.h"

float innerRadius = 120;
float trackWidth = 50;
float trackMiddle = innerRadius + 0.5*trackWidth;

enum
{
	Distant,Outside,Inside,Driver,Helicopter,Balloon,roofTop,Revolve
} view = Distant;

float carPos = 0;
float carPosX = 100;
float carPosY = 0;
float carPosZ = 0;

float height = 10;
float zoom = 50;
int windowHeight = 600;
int windowWidth = 1200;

float mouseX = 0;
float mouseY = 0;
GLUquadricObj *pointer;


using namespace std;



GLuint loadTexture(Image* image) {
	GLuint textureId;
	glGenTextures(1, &textureId); //Make room for our texture
	glBindTexture(GL_TEXTURE_2D, textureId); //Tell OpenGL which texture to edit
	//Map the image to the texture
	glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
			0,                            //0 for now
			GL_RGB,                       //Format OpenGL uses for image
			image->width, image->height,  //Width and height
			0,                            //The border of the image
			GL_RGB, //GL_RGB, because pixels are stored in RGB format
			GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
			//as unsigned numbers
			image->pixels);               //The actual pixel data
	return textureId; //Returns the id of the texture
}

GLuint _textureId; //The id of the texture

void initRendering() {
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);

	Image* image = loadBMP("track_b.bmp");
	_textureId = loadTexture(image);
	delete image;
}
void initialize(void)
{
	glClearColor(0,0,0,1);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom,windowWidth/windowHeight,1,1000);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_DEPTH_TEST);
}
void drawCar()
{
	glColor3f(1,.1,.1);
glPushMatrix();
	glTranslatef(-150,-150,-10);
		glutSolidCube(15.0f);
/*	glBegin(GL_POLYGON);				//front face
		glVertex3f(0,0,0);
		glVertex3f(0,20,0);
		glVertex3f(20,20,0);
		glVertex3f(20,0,0);
		glVertex3f(0,0,0);
	glEnd();

	glBegin(GL_LINE_STRIP);				//back face
		glVertex3f(20,0,-20);
		glVertex3f(20,20,-20);
		glVertex3f(0,20,-20);
		glVertex3f(0,0,-20);
		glVertex3f(20,0,-20);
	glEnd();

	glBegin(GL_LINES);				//edges joining back nd front faces
		glVertex3f(0,0,0);
		glVertex3f(0,0,-20);

		glVertex3f(0,20,0);
		glVertex3f(0,20,-20);

		glVertex3f(20,0,0);
		glVertex3f(20,0,-20);

		glVertex3f(20,20,0);
		glVertex3f(20,20,-20);
		glEnd();
*/
	glPushMatrix();
		glTranslatef(20,-10,0);
		glRotatef(90,0,1,0);
		gluCylinder(pointer, 5.0, 0.0, 10.0, 10, 12);
	glPopMatrix();
glPopMatrix();
}
void drawTrack()
{
glPushMatrix();
glTranslatef(100,0,0);
	glColor3f(1,1,1);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, _textureId);
	//Bottom
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	glColor3f(0.0f, 1.0f, 0.0f);
	glBegin(GL_QUADS);

	glNormal3f(0.0, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
		glVertex3f(-500.0f, -220.0f, -20.0f);
	glTexCoord2f(1.0f, 0.0f);
		glVertex3f(-500.0f, 220.0f,- 20.0f);
	glTexCoord2f(1.0f, 1.0f);
		glVertex3f(0.0f, 220.0f, -20.0f);
	glTexCoord2f(0.0f, 1.0f);
		glVertex3f(0.0f, -220.0f, -20.0f);

	glEnd();

glPopMatrix();
/*	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++)
	{
		glColor3f(0,1.0,0.0);
		glVertex3f(innerRadius*cos(i*(3.14/180)),innerRadius*sin(i*(3.14/180)),-60);
//		glVertex3f((innerRadius + trackWidth)*cos(i*(3.14/180)),(innerRadius + trackWidth)*sin(i*(3.14/180)),-60);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(int i=0;i<360;i++)
	{
		glColor3f(1.0,0,0.0);
		glVertex3f((innerRadius + trackWidth)*cos(i*(3.14/180)),(innerRadius + trackWidth)*sin(i*(3.14/180)),-60);
//		glVertex3f(innerRadius*cos(i*(3.14/180)),innerRadius*sin(i*(3.14/180)),-60);
	}
	glEnd();
	*/
/*	glPushMatrix();
	glTranslatef(-40,-20,-20);
	glColor3f(0,0,2);
	gluDisk(pointer,0,innerRadius,50,5);
	glColor3f(1,0,0);
	gluDisk(pointer,innerRadius,innerRadius + trackWidth,50,5);
	glPopMatrix();
	glPushMatrix();
		glColor3f(1,1,1);
		glTranslatef(0,0,-20);
		glutSolidCube(2.0f);
		glTranslatef(10,0,0);
		glutWireCube(4.0f);
		glTranslatef(10,20,0);
		glutSolidTeapot(5.0f);
	glPopMatrix();
*/
}
	


void move()
{
//	carPos += 0.0015;
	if(carPos > 2*PI)
	{
		carPos -= 2*PI;
	}

//	carPosX = -40 + trackMiddle * sin(carPos);
//	carPosY = -20 + trackMiddle * cos(carPos);
	
//	carPosX = trackMiddle * sin(carPos);
//	carPosY = trackMiddle * cos(carPos);
	glutPostRedisplay();
}

void projection(void )
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(zoom,windowWidth/windowHeight,1,1000);
}
void viewpoint()
{
	switch(view)
	{
		case Distant:
			gluLookAt(250,0,20*height,
				  0,0,0,
				  0,0,1);
			drawTrack();
			glTranslatef(carPosX,carPosY,carPosZ);
			glRotatef((180/PI) * carPos,0,0,-1);
			drawCar();
			break;
		case Inside:
			gluLookAt(85,0,height,
				  carPosX,carPosY,0,
				  0,0,1);
			drawTrack();
			glTranslatef(carPosX,carPosY,carPosZ);
			glRotatef((180/PI) * carPos,0,0,-1);
			drawCar();
			break;
		case Outside:
			gluLookAt(115,0,height,
				  carPosX,carPosY,0,
				  0,0,1);
			drawTrack();
			glTranslatef(carPosX,carPosY,carPosZ);
			glRotatef((180/PI) * carPos,0,0,-1);
			drawCar();
			break;
		case Driver:
			gluLookAt(2,0,height,
				  120,0,2,
				  0,0,1);
			drawCar();
			glRotatef((180/PI) * carPos,0,0,1);
			glTranslatef(-carPosX,-carPosY,carPosZ);
			drawTrack();
			break;
		case roofTop:
			gluLookAt(2,0,height,
				  120,0,2,
				  0,0,1);
			drawCar();
			glRotatef((180/PI) * carPos,0,0,1);
			glTranslatef(-carPosX,-carPosY,carPosZ);
			drawTrack();
			break;

		case Helicopter:
			gluLookAt(80*mouseX,80*mouseY,200,
				  0,0,0,
				  0,0,1);
			drawTrack();
			glTranslatef(carPosX,carPosY,carPosZ);
			glRotatef((180/PI) * carPos,0,0,-1);
			drawCar();
			break;
		case Balloon:
			gluLookAt(150,75,250,
				  80*mouseX,80*mouseY,80,
				  0,0,1);
			drawTrack();
			glTranslatef(carPosX,carPosY,carPosZ);
			glRotatef((180/PI) * carPos, 0,0,-1);
			drawCar();
			break;
		case Revolve:
			glRotatef((180/PI) * carPos, 0.0, -1.0, 0.0);
			gluLookAt(2.0, 0.0, height,
				  40.0 - carPosX, 120.0 - carPosY, carPosZ,
				  0.0, 0.0, 1.0 );
			drawCar();
			glRotatef((180/PI) * carPos, 0.0, 0.0, 1.0);
			glTranslatef(- carPosX, - carPosY, carPosZ);
			drawTrack();
			break;
	}
}
void mouse(int x, int y)
{
	mouseX = (2.0*x)/windowWidth;
	mouseY = (2.0*x)/windowHeight;
}
void keyboard(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 'q':
			height = 10;
			zoom = 50;
			view = Distant;
			break;
		case 'w':
			height = 10;
			zoom = 50;
			view = Inside;
			break;
		case 'e':
			height = 10;
			zoom = 50;
			view = Outside;
			break;
		case 'r':
			height = -10;
			zoom = 15;
			view = Driver;
			break;
		case 't':
			height = 10;
			zoom = 50;
			view = Helicopter;
			break;
		case 'y':
			height = 10;
			zoom = 50;
			view = Balloon;
			break;
		case 'u':
			height = 15;
			zoom = 25;
			view = roofTop;
			break;
		case 'i':
			height = 10;
			zoom = 50;
			view = Revolve;
			break;

	// move the car
		case 'j':
			carPosX += 1.0 * cos(carPos);
			carPosY -= 1.0 * sin(carPos);
			break;
		case 'm':
			carPosX -= 1.0 * cos(carPos);
			carPosY += 1.0 * sin(carPos);
			break;
		case 'n':
			carPos -= 0.1;
			break;
		case 'k':
			carPos += 0.1;
			break;


		case 27:
			exit(0);

	}
}

void keys(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT:
				zoom *= 1.2;
				projection();
				break;
		case GLUT_KEY_RIGHT:
				zoom /= 1.2;
				projection();
				break;
		case GLUT_KEY_UP:
				height += 1;
				projection();
				break;
		case GLUT_KEY_DOWN:
				height -= 1;
				projection();
				break;

	}
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	viewpoint();

	glutSwapBuffers();
}

void reshape(int newWidth, int newHeight)
{
	windowWidth = newWidth;
	windowHeight = newHeight;
	glViewport(0,0,windowWidth,windowHeight);
	projection();
}
/*
float R=100;
float theta = 3.14;
float eyeY = 25;
float objX = 25,objY = 25,objZ = -30;
int axisX=0,axisY = 1,axisZ = 0;
*/
/*
void draw()
{

		glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		gluLookAt(R*(sin(theta)),eyeY,R*(cos(theta)),objX,objY,objZ,axisX,axisY,axisZ);
		glTranslatef(0,0,-4);
		glScalef(.10,.10,.10);
		drawCar();
		glutSwapBuffers();
}
*/
int main(int argc,char **argv)
{
	glutInit(&argc,argv);
	glutInitWindowSize(windowWidth,windowHeight);
	glutInitWindowPosition(1,1);
	glutInitDisplayMode(GLUT_RGB|GLUT_DEPTH|GLUT_DOUBLE);
	glutCreateWindow("ABHINAV SINGI");
	initRendering();
	glutDisplayFunc(display);
	glutIdleFunc(move);
	glutPassiveMotionFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(keys);
	glEnable(GL_DEPTH_TEST);
	pointer = gluNewQuadric();
	gluQuadricDrawStyle(pointer, GLU_FILL);

	projection();
	//      glutFullScreen();
//	initialize();
	glutMainLoop();
	return 0;
}         
