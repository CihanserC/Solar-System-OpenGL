/*					16070001020			CÝHANSER ÇALIÞKAN

Camera movements:
w : forwards
s : backwards
a : turn left
d : turn right
x : turn up
z : turn down
v : straight right
c : straight left
r : move up
f : move down
q: exit
l: enable/disable lighting

-----------------------------
 Radius Data of the planets and the Sun

 Note: Calculations are made
 based on earth.

Sun     - 695,510 km
Jupiter - 69,911  km
Saturn  - 58,232 km
Uranus  - 25,362 km
Neptune - 24,622 km
Earth   - 6,371 km
Venus   - 6,052 km
Mars    - 3,390 km
Mercury - 2,440 km

-----------------------------------------

Distance of planets to sun

Note: Ratios are based on
astronomical unit(AU).

Mercury = 4
Venus   = 7
Earth   = 10
Mars    = 15
Jupiter = 52
Saturn  = 96
Uranus  = 192
Neptune = 300

------------
Rotational speeds of planets around the sun

mercury - 47.87  km/s
venus   - 35.02  km/s
earth   - 29.78  km/s
mars    - 24.077 km/s
jupiter - 13.07  km/s
saturn  - 9.63   km/s
uranus  - 6.81   km/s
Neptune - 5.43   km/s

*/

#include <GL\glut.h>
#include <windows.h>
#include "camera.h"
#include <stdio.h>
#include <stdlib.h>
#include<iostream> 
#include <stdarg.h>
#include<string> 
#include<math.h>
#include <time.h> 
//#include<tgmath.h>

#define ShowUpvector 

CCamera Camera;

//----------------------------------
// Radius Data
const GLfloat Earth_Radius = 1.0;
const GLfloat Sun_Radius = 109.2;
const GLfloat Mercury_Radius = 0.38;
const GLfloat Venus_Radius = 0.95;
const GLfloat Mars_Radius = 0.53;
const GLfloat Jupiter_Radius = 11.0;
const GLfloat Saturn_Radius = 9.1;
const GLfloat Uranus_Radius = 4.0;
const GLfloat Neptune_Radius = 3.9;

// Dist to Sun Data

const GLfloat Mercury_Dist = 4.0;
const GLfloat Venus_Dist = 7.0;
const GLfloat Earth_Dist = 10.0;
const GLfloat Mars_Dist = 15.0;
const GLfloat Jupiter_Dist = 52.0;
const GLfloat Saturn_Dist = 96.0;
const GLfloat Uranus_Dist = 192.0;
const GLfloat Neptune_Dist = 300.0;

// Velocity Data
const GLfloat Earth_Velocity = 1.0;
const GLfloat Mercury_Velocity = 1.607;
const GLfloat Venus_Velocity = 1.176;
const GLfloat Mars_Velocity = 0.8085;
const GLfloat Jupiter_Velocity = 0.4389;
const GLfloat Saturn_Velocity = 0.3234;
const GLfloat Uranus_Velocity = 0.2287;
const GLfloat Neptune_Velocity = 0.1823;

float speedMercury = 0.01607;
float speedVenus = 0.01176;
float speedEarth = 0.01 ;
float speedMars = 0.008085;
float speedJupiter = 0.004389;
float speedSaturn= 0.003234;
float speedUranus = 0.002287;
float speedNeptune = 0.001823;


// Planet RGB Data
//Sun_color =  glColor3f(1.0, 0.84, 0.25);
//Earth_color =  glColor3f(0.88, 0.66, 0.37);
//Mercury_color =  glColor3f(0.82, 0.81, 0.81);
//Venus_color =  glColor3f(0.55, 0.5, 0.52);
//Mars_color =  glColor3f(0.95, 0.31, 0.09);
//Jupiter_color =  glColor3f(0.84, 0.62, 0.5);
//Saturn_color =  glColor3f(0.82, 0.73, 0.73);
//Uranus_color =  glColor3f(0.74, 0.89, 0.9);
//Neptune_color = glColor3f(0.45, 0.68, 0.68);

//------------------------------

GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

bool lightswitch = true;

//float SunPos[3] = {0 , 0, 0};
float MercuryPos[3] = { 4 ,0, 1 };
float VenusPos[3] = { 7 ,0, 20 };
float EarthPos[3] = { 10 ,0, 30 };
float MarsPos[3] = { 15 ,0, 40 };
float JupiterPos[3] = { 52,0, 50 };
float SaturnPos[3] = { 96 ,0, 60 };
float UranusPos[3] = { 192 ,0, 70 };
float NeptunePos[3] = { 300 ,0, 80 };


 float angle = 0.0;
 float angleMercury = 0.0;
 float angleVenus = 0.0;
 float angleEarth = 0.0;
 float angleMars = 0.0;
 float angleJupiter = 0.0;
 float angleSaturn = 0.0;
 float angleUranus = 0.0;
 float angleNeptune = 0.0;


void lightInit(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };

	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 25.0);
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	bool lightswitch = true;


	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

void reshape(int x, int y)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}



void DrawOrbit(float r, float x, float z)
{
	glBegin(GL_LINE_STRIP);
	glColor3f(1.0, 0, 0);
	glTranslatef(x, 0, z);

	for (int i = 0; i < 361; i++)
	{
		glVertex3f((r  ) * (float)sin(i * PI / 180), 0, (r  ) * (float)cos(i * PI / 180));
	}
	glEnd();
}

void DrawOrbits() {

	DrawOrbit(4, 0, 0);
	DrawOrbit(7, 0, 0);
	DrawOrbit(10.1, 0, 0);
	DrawOrbit(15.0, 0, 0);
	DrawOrbit(52.0, 0, 0);
	DrawOrbit(96.0, 0, 0);
	DrawOrbit(192.0, 0, 0);
	DrawOrbit(300.0, 0, 0);
}


void idle()
{

	if (angle >= (2.0 * PI)) {
		angle = angle - (2.0 * PI);
	}
	if (angleMercury >= (2.0 * PI)) {
		angleMercury = angleMercury - (2.0 * PI);
	}
	if (angleVenus >= (2.0 * PI)) {
		angleVenus = angleVenus - (2.0 * PI);
	}
	if (angleEarth >= (2.0 * PI)) {
		angleEarth = angleEarth - (2.0 * PI);
	}
	if (angleMars >= (2.0 * PI)) {
		angleMars = angleMars - (2.0 * PI);
	}
	if (angleJupiter >= (2.0 * PI)) {
		angleJupiter = angleJupiter - (2.0 * PI);
	}
	if (angleSaturn >= (2.0 * PI)) {
		angleSaturn = angleSaturn - (2.0 * PI);
	}
	if (angleUranus >= (2.0 * PI)) {
		angleUranus = angleUranus - (2.0 * PI);
	}
	if (angleNeptune >= (2.0 * PI)) {
		angleNeptune = angleNeptune - (2.0 * PI);
	}

	 angleMercury +=speedMercury;
	 angleVenus += speedVenus;
	 angleEarth += speedEarth;
	 angleMars += speedMars;
	 angleJupiter += speedJupiter;
	 angleSaturn += speedSaturn;
	 angleUranus += speedUranus;
	 angleNeptune += speedNeptune;

	glutPostRedisplay();

}


void DrawPlanet(float radius, float y,  float z, float r, float g, float b)
{
	glPushMatrix();
	glColor3f(r, g, b);
	/*
	if (y != 0) { // if it is not sun
		glTranslatef(y + 109.2, 0, z);
	}
	else {
		glTranslatef(y, 0, z);
	}
	*/
	

	glTranslatef(y, 0, z);
	glutSolidSphere(radius, 20, 16);
	glFlush();
	glPopMatrix();

}


void OpMercury(float x) {
	
	MercuryPos[0] = x * sin(angleMercury );
	MercuryPos[2] = x * cos(angleMercury);
	
}

void OpVenus(float x) {
	VenusPos[0] = 7 * sin(angleVenus );
	VenusPos[2] = 7 * cos(angleVenus);

}


void OpEarth(float x) {
	EarthPos[0] = x * sin(angleEarth);
	EarthPos[2] = x * cos(angleEarth);
	
}

void OpMars(float x) {
	MarsPos[0] = x * sin(angleMars);
	MarsPos[2] = x * cos(angleMars);
	
}

void OpJupiter(float x) {
	JupiterPos[0] = x * sin(angleJupiter);
	JupiterPos[2] = x * cos(angleJupiter);

}

void OpSaturn(float x) {
	SaturnPos[0] = x * sin(angleSaturn);
	SaturnPos[2] = x * cos(angleSaturn );

}

void OpUranus(float x) {
	UranusPos[0] = x * sin(angleUranus);
	UranusPos[2] = x * cos(angleUranus);

}

void OpNeptune(float x) {
	NeptunePos[0] = x * sin(angleNeptune);
	NeptunePos[2] = x * cos(angleNeptune);
	
}


void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera.Render();

	//Draw the Solar System

	//DrawPlanet(radius, dist to sun_x, 0, dist to sun_z, red, green, blue);
	
	DrawOrbits();
	//Sun
	DrawPlanet(1, 0,  0, 1.0, 0.84, 0.25);
	
	//Mercury
	DrawPlanet(0.38, MercuryPos[0], MercuryPos[2], 0.82, 0.81, 0.81);
	OpMercury(4);
	
	//Venus
	DrawPlanet(0.95, VenusPos[0], VenusPos[2], 0.55, 0.5, 0.52);
	OpVenus(7);
	
	//Earth
	DrawPlanet(1.0, EarthPos[0], EarthPos[2], 0.88, 0.66, 0.37);
	OpEarth(10);


	//Mars
	DrawPlanet(0.53, MarsPos[0], MarsPos[2], 0.95, 0.31, 0.09);
	OpMars(15);


	//Jupiter
	DrawPlanet(11.0, JupiterPos[0], JupiterPos[2], 0.84, 0.62, 0.5);
	OpJupiter(52);

	//Saturn
	DrawPlanet(9.1, SaturnPos[0], SaturnPos[2], 0.82, 0.73, 0.73);
	OpSaturn(96);

	//Uranus
	DrawPlanet(4.0, UranusPos[0], UranusPos[2], 0.74, 0.89, 0.9);
	OpUranus(192);

	//Neptune
	DrawPlanet(3.9, NeptunePos[0], NeptunePos[2], 0.45, 0.68, 0.68);
	OpNeptune(300);
	
	idle();


	//finish rendering
	glFlush();
	glutSwapBuffers();

}


void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	case 'a':
		Camera.RotateY(5.0);
		Display();
		break;
	case 'd':
		Camera.RotateY(-5.0);
		Display();
		break;
	case 'w':
		Camera.MoveForward(-6.1);
		Display();
		break;
	case 's':
		Camera.MoveForward(6.1);
		Display();
		break;
	case 'x':
		Camera.RotateX(5.0);
		Display();
		break;
	case 'z':
		Camera.RotateX(-5.0);
		Display();
		break;
	case 'c':
		Camera.StrRight(-6.1);
		Display();
		break;
	case 'v':
		Camera.StrRight(6.1);
		Display();
		break;
	case 'f':
		Camera.MoveUpward(-3.3);
		Display();
		break;
	case 'r':
		Camera.MoveUpward(3.3);
		Display();
		break;
	case 'q':
		PostQuitMessage(0);
		break;
	case 'l':

		if (lightswitch == true)
		{
			glDisable(GL_LIGHT0);
			lightswitch = false;
			break;
		}
		else if (lightswitch == false)
		{
			glEnable(GL_LIGHT0);
			lightswitch = true;
			break;
		}

	}
}

int main(int argc, char **argv)
{ 
	// The sun radius is assumed 1 because realistic sun radius was corrupting the other planets.
	
	glutInit(&argc, argv);
	//glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	/*
	Camera movements :
	w: forwards
	s : backwards
	a : turn left
	d : turn right
	x : turn up
	z : turn down
	v : straight right
	c : straight left
	r : move up
	f : move down
	q : exit
	l : enable / disable lighting

	*/

	glutInitWindowSize(600, 600);
	glutCreateWindow("Solar System");
	lightInit();
	Camera.Move(Vector3D(0, 100.0, 0.0));
	Camera.RotateX(-85.0);
	Camera.MoveForward(200);
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutMainLoop();
	return 0;
}