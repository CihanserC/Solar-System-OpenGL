/*
 * Solar System OpenGL Simulation
 * Student ID: 16070001020
 * Name: CIHANSER CALISKAN
 *
 * Camera Controls:
 * w : move forwards
 * s : move backwards
 * a : turn left
 * d : turn right
 * x : look up
 * z : look down
 * v : strafe right
 * c : strafe left
 * r : move up
 * f : move down
 * q : exit
 * l : enable/disable lighting
 *
 * ========================================
 * Planetary Radius Data
 * 
 * Note: All calculations are relative to Earth's radius
 *
 * Sun     - 695,510 km (109.2x Earth)
 * Jupiter -  69,911 km (11.0x Earth)
 * Saturn  -  58,232 km (9.1x Earth)
 * Uranus  -  25,362 km (4.0x Earth)
 * Neptune -  24,622 km (3.9x Earth)
 * Earth   -   6,371 km (1.0x - baseline)
 * Venus   -   6,052 km (0.95x Earth)
 * Mars    -   3,390 km (0.53x Earth)
 * Mercury -   2,440 km (0.38x Earth)
 *
 * ========================================
 * Orbital Distance from Sun
 *
 * Note: Distances are scaled based on
 * Astronomical Units (AU)
 *
 * Mercury =   4 AU
 * Venus   =   7 AU
 * Earth   =  10 AU
 * Mars    =  15 AU
 * Jupiter =  52 AU
 * Saturn  =  96 AU
 * Uranus  = 192 AU
 * Neptune = 300 AU
 *
 * ========================================
 * Orbital Velocities Around the Sun
 *
 * Mercury - 47.87  km/s (1.607x Earth)
 * Venus   - 35.02  km/s (1.176x Earth)
 * Earth   - 29.78  km/s (1.0x - baseline)
 * Mars    - 24.077 km/s (0.809x Earth)
 * Jupiter - 13.07  km/s (0.439x Earth)
 * Saturn  -  9.63  km/s (0.323x Earth)
 * Uranus  -  6.81  km/s (0.229x Earth)
 * Neptune -  5.43  km/s (0.182x Earth)
 *
 */


#ifdef __APPLE__
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#ifdef _WIN32
#include <windows.h>
#endif
#endif

#include "camera.h"
#include "solar_system.h"
#include "texture_manager.h"
#include "starfield.h"
#include "ui_renderer.h"
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream> 
#include <stdarg.h>
#include <string> 
#include <math.h>
#include <time.h> 

#define ShowUpvector 

// Global objects
CCamera Camera;
SolarSystem* solarSystem = nullptr;
TextureManager* textureManager = nullptr;
StarField* starField = nullptr;
UIRenderer* uiRenderer = nullptr;
DeltaTime deltaTime;
FPSCounter fpsCounter;

// Window dimensions
int windowWidth = 800;
int windowHeight = 600;

// Notes: All planet data is now in Planet and SolarSystem classes
// These constants are kept for reference

// Material properties for lighting
GLfloat diffuseMaterial[4] = { 0.5, 0.5, 0.5, 1.0 };

// Lighting toggle state
bool lightswitch = true;

// Mouse control variables
bool mouseEnabled = true;
int lastMouseX = -1;
int lastMouseY = -1;
bool firstMouse = true;
float mouseSensitivity = 0.2f;

// Simulation control
bool isPaused = false;

// Keyboard state for smooth movement
bool keys[256] = {false};
float moveSpeed = 0.5f;  // Hareket hızı (smooth için daha küçük)


/**
 * Initialize lighting and material properties
 */
void lightInit(void)
{
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat mat_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };  // Sun at center
	GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	// Set background color to black (space)
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_DEPTH_TEST);
	
	// Alpha blending (for trails)
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	// Configure material properties
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMaterial);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
	
	// Configure light source (G?ne?'ten yay?lacak)
	glLightfv(GL_LIGHT0, GL_POSITION, light_position);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	
	// Light attenuation
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.0);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.0);
	
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	// Enable color materials
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

/**
 * Reshape callback - handles window resizing
 * @param x New window width
 * @param y New window height
 */
void reshape(int x, int y)
{
	windowWidth = x;
	windowHeight = y;
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40.0, (GLdouble)x / (GLdouble)y, 0.5, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glViewport(0, 0, x, y);
}



/**
 * Main display callback - renders the entire solar system
 */
void Display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	Camera.Render();

	// Render starfield (background)
	if (starField) {
		starField->render();
	}

	// Render solar system
	if (solarSystem) {
		solarSystem->render();
	}

	// Render UI
	if (uiRenderer) {
		uiRenderer->render(solarSystem, windowWidth, windowHeight);
	}
	
	// Show PAUSE indicator if paused
	if (isPaused) {
		glMatrixMode(GL_PROJECTION);
		glPushMatrix();
		glLoadIdentity();
		gluOrtho2D(0, windowWidth, 0, windowHeight);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glLoadIdentity();
		
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		
		// Draw semi-transparent background
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(0.0f, 0.0f, 0.0f, 0.5f);
		glBegin(GL_QUADS);
		glVertex2f(windowWidth/2 - 100, windowHeight/2 - 30);
		glVertex2f(windowWidth/2 + 100, windowHeight/2 - 30);
		glVertex2f(windowWidth/2 + 100, windowHeight/2 + 30);
		glVertex2f(windowWidth/2 - 100, windowHeight/2 + 30);
		glEnd();
		glDisable(GL_BLEND);
		
		// Draw text
		glColor3f(1.0f, 1.0f, 0.0f);
		glRasterPos2f(windowWidth/2 - 40, windowHeight/2 - 5);
		const char* pauseText = "PAUSED";
		for (const char* c = pauseText; *c != '\0'; c++) {
			glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
		}
		
		glEnable(GL_DEPTH_TEST);
		if (lightswitch) glEnable(GL_LIGHTING);
		
		glPopMatrix();
		glMatrixMode(GL_PROJECTION);
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
	}

	// Update FPS
	fpsCounter.update();

	// Finish rendering
	glFlush();
	glutSwapBuffers();
}

/**
 * Idle callback - updates animation state
 */
void idle()
{
	// Skip updates if paused
	if (isPaused) {
		glutPostRedisplay();  // Still redraw (for UI updates)
		return;
	}
	
	// Update delta time
	deltaTime.update();
	
	// Smooth camera movement based on key states
	if (keys['w'] || keys['W']) {
		Camera.MoveForward(-moveSpeed);
	}
	if (keys['s'] || keys['S']) {
		Camera.MoveForward(moveSpeed);
	}
	if (keys['a'] || keys['A']) {
		Camera.RotateY(moveSpeed * 0.5f);
	}
	if (keys['d'] || keys['D']) {
		Camera.RotateY(-moveSpeed * 0.5f);
	}
	if (keys['x'] || keys['X']) {
		Camera.RotateX(moveSpeed * 0.5f);
	}
	if (keys['z'] || keys['Z']) {
		Camera.RotateX(-moveSpeed * 0.5f);
	}
	if (keys['c'] || keys['C']) {
		Camera.StrRight(-moveSpeed);
	}
	if (keys['v'] || keys['V']) {
		Camera.StrRight(moveSpeed);
	}
	if (keys['r'] || keys['R']) {
		Camera.MoveUpward(moveSpeed * 0.5f);
	}
	if (keys['f'] || keys['F']) {
		Camera.MoveUpward(-moveSpeed * 0.5f);
	}
	
	// Update solar system
	if (solarSystem) {
		solarSystem->update(deltaTime.getDelta());
	}

	// Request display update
	glutPostRedisplay();
}

/**
 * Mouse motion callback - handles camera rotation with mouse
 * @param x Current mouse x-coordinate
 * @param y Current mouse y-coordinate
 */
void mouseMotion(int x, int y)
{
	if (!mouseEnabled) return;
	
	// Initialize on first mouse movement
	if (firstMouse) {
		lastMouseX = x;
		lastMouseY = y;
		firstMouse = false;
		return;
	}
	
	// Calculate mouse movement
	int deltaX = x - lastMouseX;
	int deltaY = y - lastMouseY;
	
	// Update camera rotation
	if (deltaX != 0) {
		Camera.RotateY(-deltaX * mouseSensitivity);
	}
	if (deltaY != 0) {
		Camera.RotateX(-deltaY * mouseSensitivity);
	}
	
	// Store current position
	lastMouseX = x;
	lastMouseY = y;
}

/**
 * Mouse button callback - handles mouse clicks
 * @param button Mouse button that was pressed/released
 * @param state Button state (GLUT_DOWN or GLUT_UP)
 * @param x Mouse x-coordinate at time of click
 * @param y Mouse y-coordinate at time of click
 */
void mouseButton(int button, int state, int x, int y)
{
	// Reset mouse tracking on button press
	if (state == GLUT_DOWN) {
		lastMouseX = x;
		lastMouseY = y;
		firstMouse = false;
	}
}

/**
 * Keyboard up callback - handles key release for smooth movement
 * @param key The key that was released
 * @param x Mouse x-coordinate at time of key release
 * @param y Mouse y-coordinate at time of key release
 */
void KeyboardUp(unsigned char key, int x, int y)
{
	// Mark key as released
	keys[key] = false;
}


/**
 * Keyboard callback - handles user input
 * @param key The key that was pressed
 * @param x Mouse x-coordinate at time of keypress
 * @param y Mouse y-coordinate at time of keypress
 */
void Keyboard(unsigned char key, int x, int y)
{
	// Mark key as pressed for smooth movement
	keys[key] = true;
	
	switch (key)
	{
	// Camera controls are now handled in idle() for smooth movement
	// W, A, S, D, X, Z, C, V, R, F are processed there
	
	// System controls
	case 'q':  // Quit application
		#ifdef _WIN32
		PostQuitMessage(0);
		#else
		exit(0);
		#endif
		break;
	case 'l':  // Toggle lighting on/off
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
		break;
	case 'm':  // Toggle mouse control
	case 'M':
		mouseEnabled = !mouseEnabled;
		firstMouse = true;  // Reset mouse tracking
		std::cout << "Mouse control: " << (mouseEnabled ? "ENABLED" : "DISABLED") << std::endl;
		break;
	case 'p':  // Pause/Resume simulation
	case 'P':
		isPaused = !isPaused;
		std::cout << "Simulation: " << (isPaused ? "PAUSED" : "RUNNING") << std::endl;
		break;
		
	// New features
	case 't':  // Toggle trails
	case 'T':
		if (solarSystem) {
			solarSystem->toggleTrails();
		}
		break;
	case 'o':  // Toggle orbits
	case 'O':
		if (solarSystem) {
			solarSystem->toggleOrbits();
		}
		break;
	case 'i':  // Toggle info panel
	case 'I':
		if (uiRenderer) {
			uiRenderer->toggleInfo();
		}
		break;
	case 'h':  // Toggle help
	case 'H':
		if (uiRenderer) {
			uiRenderer->toggleHelp();
		}
		break;
	case '+':  // Increase time scale
	case '=':
		if (solarSystem) {
			solarSystem->increaseTimeScale();
		}
		break;
	case '-':  // Decrease time scale
	case '_':
		if (solarSystem) {
			solarSystem->decreaseTimeScale();
		}
		break;
		
	// Planet selection (1-8)
	case '1':
		if (solarSystem) solarSystem->selectPlanet(0);  // Mercury
		break;
	case '2':
		if (solarSystem) solarSystem->selectPlanet(1);  // Venus
		break;
	case '3':
		if (solarSystem) solarSystem->selectPlanet(2);  // Earth
		break;
	case '4':
		if (solarSystem) solarSystem->selectPlanet(3);  // Mars
		break;
	case '5':
		if (solarSystem) solarSystem->selectPlanet(4);  // Jupiter
		break;
	case '6':
		if (solarSystem) solarSystem->selectPlanet(5);  // Saturn
		break;
	case '7':
		if (solarSystem) solarSystem->selectPlanet(6);  // Uranus
		break;
	case '8':
		if (solarSystem) solarSystem->selectPlanet(7);  // Neptune
		break;
	case '0':  // Clear selection
		if (solarSystem) solarSystem->clearSelection();
		break;
	}
}

/**
 * Main entry point
 * Initializes OpenGL, sets up window, and starts the main loop
 */
int main(int argc, char **argv)
{ 
	// Initialize GLUT
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	
	// Create window
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Solar System - OpenGL Simulation [Enhanced]");
	
	// Initialize lighting and materials
	lightInit();
	
	// Initialize texture manager and load textures
	textureManager = new TextureManager();
	std::cout << "Loading planet textures..." << std::endl;
	textureManager->loadPlanetTextures();
	
	// Initialize solar system
	solarSystem = new SolarSystem();
	
	// Apply textures to planets (if available)
	if (solarSystem->getPlanetCount() > 0) {
		const char* planetNames[] = {"mercury", "venus", "earth", "mars", 
		                             "jupiter", "saturn", "uranus", "neptune"};
		for (int i = 0; i < 8 && i < solarSystem->getPlanetCount(); i++) {
			Planet* planet = solarSystem->getPlanet(i);
			if (planet) {
				GLuint texID = textureManager->getTexture(planetNames[i]);
				if (texID > 0) {
					planet->setTexture(texID);
					std::cout << "Applied texture to " << planetNames[i] << std::endl;
				}
			}
		}
		
		// Special handling for Earth - day/night textures
		Planet* earth = solarSystem->getPlanet(2); // Earth is 3rd planet (index 2)
		if (earth) {
			GLuint dayTexID = textureManager->getTexture("earth_day");
			GLuint nightTexID = textureManager->getTexture("earth_night");
			
			if (dayTexID > 0) {
				earth->setTexture(dayTexID);
				std::cout << "Applied day texture to Earth" << std::endl;
			}
			if (nightTexID > 0) {
				earth->setNightTexture(nightTexID);
				std::cout << "Applied night texture to Earth (day/night cycle enabled!)" << std::endl;
			}
		}
		
		// Apply Saturn ring texture
		Planet* saturn = solarSystem->getPlanet(5); // Saturn is 6th planet (index 5)
		if (saturn) {
			GLuint ringTexID = textureManager->getTexture("saturn_ring");
			if (ringTexID > 0) {
				saturn->setRingTexture(ringTexID);
				std::cout << "Applied ring texture to Saturn" << std::endl;
			}
		}
	}
	
	// Initialize starfield
	starField = new StarField(5000, 1000.0f);
	
	// Initialize UI renderer
	uiRenderer = new UIRenderer();
	uiRenderer->setFPSCounter(&fpsCounter);
	
	// Set initial camera position and orientation
	Camera.Move(SF3dVector{0, 100.0, 0.0});    // Position camera above the plane
	Camera.RotateX(-85.0);                      // Look down at the solar system
	Camera.MoveForward(200);                    // Move back for better view
	
	// Register callback functions
	glutDisplayFunc(Display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(Keyboard);
	glutKeyboardUpFunc(KeyboardUp);     // Key release callback for smooth movement
	glutIdleFunc(idle);
	glutMotionFunc(mouseMotion);        // Mouse drag callback
	glutPassiveMotionFunc(mouseMotion); // Mouse move callback
	glutMouseFunc(mouseButton);         // Mouse button callback
	
	// Print controls
	std::cout << "========================================" << std::endl;
	std::cout << "Solar System OpenGL - Enhanced Version" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << "Camera Controls:" << std::endl;
	std::cout << "  MOUSE - Look around (drag or move)" << std::endl;
	std::cout << "  W/S - Forward/Backward" << std::endl;
	std::cout << "  A/D - Turn Left/Right" << std::endl;
	std::cout << "  X/Z - Look Up/Down" << std::endl;
	std::cout << "  C/V - Strafe Left/Right" << std::endl;
	std::cout << "  R/F - Move Up/Down" << std::endl;
	std::cout << std::endl;
	std::cout << "Features:" << std::endl;
	std::cout << "  P - Pause/Resume Simulation" << std::endl;
	std::cout << "  M - Toggle Mouse Control" << std::endl;
	std::cout << "  T - Toggle Trails" << std::endl;
	std::cout << "  O - Toggle Orbits" << std::endl;
	std::cout << "  I - Toggle Info Panel" << std::endl;
	std::cout << "  H - Toggle Help" << std::endl;
	std::cout << "  +/- - Speed Up/Slow Down" << std::endl;
	std::cout << "  1-8 - Select Planet" << std::endl;
	std::cout << "  0 - Clear Selection" << std::endl;
	std::cout << "  L - Toggle Lighting" << std::endl;
	std::cout << "  Q - Quit" << std::endl;
	std::cout << "========================================" << std::endl;
	std::cout << std::endl;
	std::cout << "Note: Textures loaded from 'textures/' folder" << std::endl;
	std::cout << "      If textures not found, solid colors will be used" << std::endl;
	std::cout << std::endl;
	
	// Enter main event loop
	glutMainLoop();
	
	// Cleanup
	delete solarSystem;
	delete textureManager;
	delete starField;
	delete uiRenderer;
	
	return 0;
}