/*
*		This Code Was Created By Jeff Molofee 2000
*		A HUGE Thanks To Fredric Echols For Cleaning Up
*		And Optimizing This Code, Making It More Flexible!
*		If You've Found This Code Useful, Please Let Me Know.
*		Visit My Site At nehe.gamedev.net
*/

#include <windows.h>		// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
#include <texture.h>
#include <iostream>
#include <Model_3DS.h>
#include <camera.h>
#include <3DTexture.h>
#include <SOIL2.h>
#include "Manager.cpp"

#define _CRT_SECURE_NO_WARNINGS


HDC			hDC = NULL;		// Private GDI Device Context
HGLRC		hRC = NULL;		// Permanent Rendering Context
HWND		hWnd = NULL;		// Holds Our Window Handle
HINSTANCE	hInstance;		// Holds The Instance Of The Application

bool	keys[256];			// Array Used For The Keyboard Routine
bool	active = TRUE;		// Window Active Flag Set To TRUE By Default
bool	fullscreen = TRUE;	// Fullscreen Flag Set To Fullscreen Mode By Default



LRESULT	CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);	// Declaration For WndProc

GLvoid ReSizeGLScene(GLsizei width, GLsizei height)		// Resize And Initialize The GL Window
{
	if (height == 0)										// Prevent A Divide By Zero By
	{
		height = 1;										// Making Height Equal One
	}

	glViewport(0, 0, width, height);						// Reset The Current Viewport

	glMatrixMode(GL_PROJECTION);						// Select The Projection Matrix
	glLoadIdentity();									// Reset The Projection Matrix

														// Calculate The Aspect Ratio Of The Window
	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100000.0f);

	glMatrixMode(GL_MODELVIEW);							// Select The Modelview Matrix
	glLoadIdentity();									// Reset The Modelview Matrix
}

double angle;
GLuint Front ,Back ,Left ,Right ,Up ,Down,carpet,door,face,grassImageID;
float XfocusCamera;
float ZfocusCamera;
float xCamera;
float yCamera;
float zCamera;
float d=0.5;


void cameraControl();
void initCameraPosition();
 Camera MyCamera;

 Model_3DS toy;
 GLfloat toyX = -100,toyY=200,toyZ=-100;
void initAriPlaneModels(){
	toy.Load("B 777 200.3ds");
	toy.Materials[0].tex.Load("body-france.bmp");
	toy.Materials[1].tex.Load("engine.bmp");
	toy.Materials[2].tex.Load("turbine.bmp");
	toy.Materials[3].tex.Load("weels.bmp");
}
void settingAriplaneModel(){

	glPushMatrix();
	toyX+=10;
	toyZ-=10;
	glTranslated(toyX,toyY,toyX);
	toy.pos.x=0;
	toy.pos.y=0;
	toy.pos.z=100;
	toy.Draw();
	glPopMatrix();

}



void cameraControl()
{
	MyCamera.Render();




	if (keys['S'])    		MyCamera.MoveForward(-3) ;
    if (keys['W'])			MyCamera.MoveForward( 3) ;
	if (keys[VK_RIGHT])			MyCamera.RotateY(-10);
    if (keys[VK_LEFT])		    MyCamera.RotateY(10);
	if (keys[VK_DOWN])        ZfocusCamera++; 
	if (keys[VK_UP])      ZfocusCamera--; 
	if (keys['A'])	    MyCamera.MoveRight(-3);
	if (keys['D'])		MyCamera.MoveRight(3);
	if(keys[VK_NUMPAD8]) MyCamera.MoveUpward(5);
		if(keys[VK_NUMPAD5]) MyCamera.MoveUpward(-5);



	gluLookAt(xCamera,yCamera,zCamera,XfocusCamera,ZfocusCamera,0,0,1,0);
	
}
void initCameraPosition()
{

 angle=0;
 XfocusCamera=0;
 ZfocusCamera=100;
 xCamera=0;
 yCamera=100;
 zCamera=10;
 d=1;
}

void initSkyBox(){
	Front = SOIL_load_OGL_texture("front.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
	Back = SOIL_load_OGL_texture("right.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
	Left = SOIL_load_OGL_texture("left.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
	Right = SOIL_load_OGL_texture("back.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
	Up = SOIL_load_OGL_texture("top.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
	Down = SOIL_load_OGL_texture("buttom.png", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);


	face =  SOIL_load_OGL_texture("bricks.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
  door =  SOIL_load_OGL_texture("door1.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);
  carpet =  SOIL_load_OGL_texture("carpet.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);

  grassImageID=  SOIL_load_OGL_texture("grass_texture.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID,
					SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_COMPRESS_TO_DXT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	//void glTexEnvi(GLenum target, GLenum pname, GLint param);
	//GL_ADD
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	//glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_BLEND);
	

}

int a = 0,b=0;

void drawRoom(int w,int h,int d){
	glBindTexture(GL_TEXTURE_2D,face);
	//front face
	glBegin(GL_QUADS);

	//First part	
	glTexCoord2d(0,0);
	glVertex3d(0,0,0);
	
	glTexCoord2d(0,1);
	glVertex3d(0,h,0);
	
	glTexCoord2d(1,1);
	glVertex3d(w/4,h,0);
	
	glTexCoord2d(1,0);
	glVertex3d(w/4,0,0);

	//second part
		glTexCoord2d(0,0);

	glVertex3d(w/4,2*h/3,0);
		glTexCoord2d(0,1);

	glVertex3d(w/4,h,0);
		glTexCoord2d(1,1);

	glVertex3d(3*w/4,h,0);
		glTexCoord2d(1,0);

	glVertex3d(3*w/4,2*h/3,0);

	//third part
			glTexCoord2d(0,0);

	glVertex3d(3*w/4,0,0);
			glTexCoord2d(0,1);

	glVertex3d(3*w/4,h,0);
			glTexCoord2d(1,1);

	glVertex3d(w,h,0);
			glTexCoord2d(1,0);

	glVertex3d(w,0,0);


	glEnd();

	
	//back face
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);

	glVertex3d(0,0,d);
		glTexCoord2d(0,1);

	glVertex3d(0,h,d);
		glTexCoord2d(1,1);

	glVertex3d(w,h,d);
		glTexCoord2d(1,0);

	glVertex3d(w,0,d);
	glEnd();
	
	//right face
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(w,0,0);
	glTexCoord2d(0,1);
	glVertex3d(w,h,0);
	glTexCoord2d(1,1);
	glVertex3d(w,h,d);
	glTexCoord2d(1,0);
	glVertex3d(w,0,d);
	glEnd();
	
	//left face
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(0,0,0);
	glTexCoord2d(0,1);
	glVertex3d(0,h,0);
	glTexCoord2d(1,1);
	glVertex3d(0,h,d);
	glTexCoord2d(1,0);
	glVertex3d(0,0,d);
	glEnd();
	
	//up face
	glBegin(GL_QUADS);
		glTexCoord2d(0,0);
glVertex3d(0,h,0);
	glTexCoord2d(0,1);
	glVertex3d(0,h,d);
	glTexCoord2d(1,1);
	glVertex3d(w,h,d);
	glTexCoord2d(1,0);
	glVertex3d(w,h,0);
	glEnd();
	
	//bottom face 
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D,carpet);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);  glVertex3d(0,0,0);
	glTexCoord2d(0,1);  glVertex3d(0,0,d);
	glTexCoord2d(1,1);	glVertex3d(w,0,d);
	glTexCoord2d(1,0);  glVertex3d(w,0,0);
	glEnd();
	glPopMatrix();
	//doors
	//left door
	glPushMatrix();
	glTranslated(a,0,0);
	glBindTexture(GL_TEXTURE_2D,door);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(w/4,0,0);
	glTexCoord2d(0,1);
	glVertex3d(w/4,2*h/3,0);
	glTexCoord2d(1,1);
	glVertex3d(2*w/4,2*h/3,0);
	glTexCoord2d(1,0);
	glVertex3d(2*w/4,0,0);
	glEnd();
	glPopMatrix();
	
	glPushMatrix();
	glTranslated(b,0,0);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(2*w/4,0,0);
	glTexCoord2d(0,1);
	glVertex3d(2*w/4,2*h/3,0);
	glTexCoord2d(1,1);
	glVertex3d(3*w/4,2*h/3,0);
	glTexCoord2d(1,0);
	glVertex3d(3*w/4,0,0);
	glEnd();
	glPopMatrix();

	if(keys[VK_ADD]) { a=-w/4; b=w/4;}
	if(keys[VK_SUBTRACT]) { a=0; b=0;}
	
}


void baseGrassGround(float high,float width)
{
	float hWidth=width/2;
	float hHigh=high/2;
	glBindTexture(GL_TEXTURE_2D,grassImageID);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3f(-hWidth,0,hHigh);
	glTexCoord2d(1,0);
	glVertex3f(hWidth,0,hHigh);
	glTexCoord2d(1,1);
	glVertex3f(hWidth,0,-hHigh);
	glTexCoord2d(0,1);
	glVertex3f(-hWidth,0,-hHigh);
	   
	glEnd();
}

void Draw_Skybox(float x, float y, float z, float width, float height, float length)
{
	
	// Center the Skybox around the given x,y,z position
	x = x - width / 2;
	y = y - height / 2;
	z = z - length / 2;
	glEnable(GL_TEXTURE_2D);

	// Draw Front side
	glBindTexture(GL_TEXTURE_2D, Front);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, Back);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, Left);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z + length);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z);
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D, Right);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y + height, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y + height, z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D, Up);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
			glTexCoord2f(0.0f, 1.0f); glVertex3f(x, y + height, z);

					glTexCoord2f(1.0f, 1.0f); glVertex3f(x, y + height, z + length);
								glTexCoord2f(1.0f, 0.0f); glVertex3f(x + width, y + height, z + length);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y + height, z);

	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D,Down);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, 0x812F);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, 0x812F);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 0.0f); glVertex3f(x, y, z);
	glTexCoord2f(1.0f, 0.0f); glVertex3f(x, y, z + length);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(x + width, y, z + length);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y, z);
	glEnd();

	glColor3f(1, 1, 1);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}
int wall,elevdoor;
void Cube(int x,int y,int z,int texture){
	float vertices[]=
	{
		//front face
		x,y,z,
		x,y+1,z,
		x+1,y+1,z,
		x+1,y,z,
		//back face
		x,y,z+1,
		x,y+1,z+1,
		x+1,y+1,z+1,
		x+1,y,z+1,
		//right face
		x+1,y,z,
		x+1,y+1,z,
		x+1,y+1,z+1,
		x+1,y,z+1,
		//left side
		x,y,z,
		x,y+1,z,
		x,y+1,z+1,
		x,y,z+1,
		//up face
		x,y+1,z,
		x,y+1,z+1,
		x+1,y+1,z+1,
		x+1,y+1,z,
		//bottom side
		x,y,z,
		x,y,z+1,
		x+1,y,z+1,
		x+1,y,z,	
	};	

	//front face with door
	glBindTexture(GL_TEXTURE_2D,elevdoor);
	glBegin(GL_QUADS);
	glTexCoord2d(0,0);
	glVertex3d(vertices[0],vertices[1],vertices[2]);
	glTexCoord2d(0,1);
	glVertex3d(vertices[3],vertices[4],vertices[5]);
	glTexCoord2d(1,1);
	glVertex3d(vertices[6],vertices[7],vertices[8]);
	glTexCoord2d(1,0);
	glVertex3d(vertices[9],vertices[10],vertices[11]);
	glEnd();
	glBindTexture(GL_TEXTURE_2D,texture);
	glBegin(GL_QUADS);
	for (int i = 12; i < 72; i+=12)
	{
		glTexCoord2d(0,0);
		glVertex3d(vertices[i],vertices[i+1],vertices[i+2]);
		glTexCoord2d(0,1);
		glVertex3d(vertices[i+3],vertices[i+4],vertices[i+5]);
		glTexCoord2d(1,1);
		glVertex3d(vertices[i+6],vertices[i+7],vertices[i+8]);
		glTexCoord2d(1,0);
		glVertex3d(vertices[i+9],vertices[i+10],vertices[i+11]);
	}
	glEnd();
}
int c=0;
void Elevator(int x,int y,int z){
	glTranslated(0,c,0);
	Cube(x,y,z,wall);
	//logic
	if(keys[VK_NUMPAD0]) c=0;
	if(keys[VK_NUMPAD1]) c=1;
	if(keys[VK_NUMPAD2]) c=2;
	if(keys[VK_NUMPAD3]) c=3;
	if(keys[VK_NUMPAD4]) c=4;
	if(keys[VK_NUMPAD5]) c=5;
	if(keys[VK_NUMPAD6]) c=6;
	if(keys[VK_NUMPAD7]) c=7;
	if(keys[VK_NUMPAD8]) c=8;
	if(keys[VK_NUMPAD9]) c=9;
}




int InitGL(GLvoid)										// All Setup For OpenGL Goes Here
{


	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);				// Black Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	// Really Nice Perspective Calculations

	//enable texture 
	initCameraPosition();
	glEnable(GL_TEXTURE_2D);
	face=LoadTexture("bricks.bmp",255);
	door=LoadTexture("door1.bmp",255);
	carpet=LoadTexture("carpet.bmp",255);
	wall=LoadTexture("iron.bmp");
	elevdoor=LoadTexture("elevdoor.bmp");

	initSkyBox();
	initAriPlaneModels();
	return TRUE;										// Initialization Went OK
}

void DrawGLScene(GLvoid)									// Here's Where We Do All The Drawing
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear Screen And Depth Buffer
	glLoadIdentity();	
	cameraControl();

	
	Draw_Skybox(-50, 0, -500, 4000, 2000, 10000);
	baseGrassGround(800,800);
	drawRoom(30,20,20);
	glPushMatrix();
	glScaled(10,5,5);
	Elevator(50,50,50);
	glPopMatrix();
	settingAriplaneModel();
	glFlush();											// Done Drawing The Quad	

														//DO NOT REMOVE THIS
	SwapBuffers(hDC);
}
















GLvoid KillGLWindow(GLvoid)								// Properly Kill The Window
{
	if (fullscreen)										// Are We In Fullscreen Mode?
	{
		ChangeDisplaySettings(NULL, 0);					// If So Switch Back To The Desktop
		ShowCursor(TRUE);								// Show Mouse Pointer
	}

	if (hRC)											// Do We Have A Rendering Context?
	{
		if (!wglMakeCurrent(NULL, NULL))					// Are We Able To Release The DC And RC Contexts?
		{
			MessageBox(NULL, "Release Of DC And RC Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}

		if (!wglDeleteContext(hRC))						// Are We Able To Delete The RC?
		{
			MessageBox(NULL, "Release Rendering Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		}
		hRC = NULL;										// Set RC To NULL
	}

	if (hDC && !ReleaseDC(hWnd, hDC))					// Are We Able To Release The DC
	{
		MessageBox(NULL, "Release Device Context Failed.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hDC = NULL;										// Set DC To NULL
	}

	if (hWnd && !DestroyWindow(hWnd))					// Are We Able To Destroy The Window?
	{
		MessageBox(NULL, "Could Not Release hWnd.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hWnd = NULL;										// Set hWnd To NULL
	}

	if (!UnregisterClass("OpenGL", hInstance))			// Are We Able To Unregister Class
	{
		MessageBox(NULL, "Could Not Unregister Class.", "SHUTDOWN ERROR", MB_OK | MB_ICONINFORMATION);
		hInstance = NULL;									// Set hInstance To NULL
	}
}



/*	This Code Creates Our OpenGL Window.  Parameters Are:					*
*	title			- Title To Appear At The Top Of The Window				*
*	width			- Width Of The GL Window Or Fullscreen Mode				*
*	height			- Height Of The GL Window Or Fullscreen Mode			*
*	bits			- Number Of Bits To Use For Color (8/16/24/32)			*
*	fullscreenflag	- Use Fullscreen Mode (TRUE) Or Windowed Mode (FALSE)	*/

BOOL CreateGLWindow(char* title, int width, int height, int bits, bool fullscreenflag)
{
	GLuint		PixelFormat;			// Holds The Results After Searching For A Match
	WNDCLASS	wc;						// Windows Class Structure
	DWORD		dwExStyle;				// Window Extended Style
	DWORD		dwStyle;				// Window Style
	RECT		WindowRect;				// Grabs Rectangle Upper Left / Lower Right Values
	WindowRect.left = (long)0;			// Set Left Value To 0
	WindowRect.right = (long)width;		// Set Right Value To Requested Width
	WindowRect.top = (long)0;				// Set Top Value To 0
	WindowRect.bottom = (long)height;		// Set Bottom Value To Requested Height

	fullscreen = fullscreenflag;			// Set The Global Fullscreen Flag

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = NULL;									// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu
	wc.lpszClassName = "OpenGL";								// Set The Class Name

	if (!RegisterClass(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL, "Failed To Register The Window Class.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;											// Return FALSE
	}

	if (fullscreen)												// Attempt Fullscreen Mode?
	{
		DEVMODE dmScreenSettings;								// Device Mode
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));	// Makes Sure Memory's Cleared
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);		// Size Of The Devmode Structure
		dmScreenSettings.dmPelsWidth = width;				// Selected Screen Width
		dmScreenSettings.dmPelsHeight = height;				// Selected Screen Height
		dmScreenSettings.dmBitsPerPel = bits;					// Selected Bits Per Pixel
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		// Try To Set Selected Mode And Get Results.  NOTE: CDS_FULLSCREEN Gets Rid Of Start Bar.
		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			// If The Mode Fails, Offer Two Options.  Quit Or Use Windowed Mode.
			if (MessageBox(NULL, "The Requested Fullscreen Mode Is Not Supported By\nYour Video Card. Use Windowed Mode Instead?", "NeHe GL", MB_YESNO | MB_ICONEXCLAMATION) == IDYES)
			{
				fullscreen = FALSE;		// Windowed Mode Selected.  Fullscreen = FALSE
			}
			else
			{
				// Pop Up A Message Box Letting User Know The Program Is Closing.
				MessageBox(NULL, "Program Will Now Close.", "ERROR", MB_OK | MB_ICONSTOP);
				return FALSE;									// Return FALSE
			}
		}
	}

	if (fullscreen)												// Are We Still In Fullscreen Mode?
	{
		dwExStyle = WS_EX_APPWINDOW;								// Window Extended Style
		dwStyle = WS_POPUP;										// Windows Style
		ShowCursor(FALSE);										// Hide Mouse Pointer
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;			// Window Extended Style
		dwStyle = WS_OVERLAPPEDWINDOW;							// Windows Style
	}

	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);		// Adjust Window To True Requested Size

																	// Create The Window
	if (!(hWnd = CreateWindowEx(dwExStyle,							// Extended Style For The Window
		"OpenGL",							// Class Name
		title,								// Window Title
		dwStyle |							// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		WindowRect.right - WindowRect.left,	// Calculate Window Width
		WindowRect.bottom - WindowRect.top,	// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL)))								// Dont Pass Anything To WM_CREATE
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Window Creation Error.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	static	PIXELFORMATDESCRIPTOR pfd =				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		bits,										// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	if (!(hDC = GetDC(hWnd)))							// Did We Get A Device Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Device Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))	// Did Windows Find A Matching Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Find A Suitable PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!SetPixelFormat(hDC, PixelFormat, &pfd))		// Are We Able To Set The Pixel Format?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Set The PixelFormat.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!(hRC = wglCreateContext(hDC)))				// Are We Able To Get A Rendering Context?
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Create A GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	if (!wglMakeCurrent(hDC, hRC))					// Try To Activate The Rendering Context
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Can't Activate The GL Rendering Context.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	ShowWindow(hWnd, SW_SHOW);						// Show The Window
	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	SetFocus(hWnd);									// Sets Keyboard Focus To The Window
	ReSizeGLScene(width, height);					// Set Up Our Perspective GL Screen

	if (!InitGL())									// Initialize Our Newly Created GL Window
	{
		KillGLWindow();								// Reset The Display
		MessageBox(NULL, "Initialization Failed.", "ERROR", MB_OK | MB_ICONEXCLAMATION);
		return FALSE;								// Return FALSE
	}

	return TRUE;									// Success
}

LRESULT CALLBACK WndProc(HWND	hWnd,			// Handle For This Window
	UINT	uMsg,			// Message For This Window
	WPARAM	wParam,			// Additional Message Information
	LPARAM	lParam)			// Additional Message Information
{
	static PAINTSTRUCT ps;

	switch (uMsg)									// Check For Windows Messages
	{
	case WM_PAINT:
		DrawGLScene();
		BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_TIMER:
		DrawGLScene();
		return 0;

	case WM_ACTIVATE:							// Watch For Window Activate Message
	{
		if (!HIWORD(wParam))					// Check Minimization State
		{
			active = TRUE;						// Program Is Active
		}
		else
		{
			active = FALSE;						// Program Is No Longer Active
		}

		return 0;								// Return To The Message Loop
	}

	case WM_SYSCOMMAND:							// Intercept System Commands
	{
		switch (wParam)							// Check System Calls
		{
		case SC_SCREENSAVE:					// Screensaver Trying To Start?
		case SC_MONITORPOWER:				// Monitor Trying To Enter Powersave?
			return 0;							// Prevent From Happening
		}
		break;									// Exit
	}

	case WM_CLOSE:								// Did We Receive A Close Message?
	{
		PostQuitMessage(0);						// Send A Quit Message
		return 0;								// Jump Back
	}

	case WM_KEYDOWN:							// Is A Key Being Held Down?
	{
		keys[wParam] = TRUE;					// If So, Mark It As TRUE
		return 0;								// Jump Back
	}

	case WM_KEYUP:								// Has A Key Been Released?
	{
		keys[wParam] = FALSE;					// If So, Mark It As FALSE
		return 0;								// Jump Back
	}

	case WM_SIZE:								// Resize The OpenGL Window
	{
		ReSizeGLScene(LOWORD(lParam), HIWORD(lParam));  // LoWord=Width, HiWord=Height
		return 0;								// Jump Back
	}
	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE	hInstance,			// Instance
	HINSTANCE	hPrevInstance,		// Previous Instance
	LPSTR		lpCmdLine,			// Command Line Parameters
	int			nCmdShow)			// Window Show State
{
	MSG		msg;									// Windows Message Structure
	BOOL	done = FALSE;								// Bool Variable To Exit Loop

														// Ask The User Which Screen Mode They Prefer
														//if (MessageBox(NULL,"Would You Like To Run In Fullscreen Mode?", "Start FullScreen?",MB_YESNO|MB_ICONQUESTION)==IDNO)
	{
		fullscreen = FALSE;							// Windowed Mode
	}

	// Create Our OpenGL Window
	if (!CreateGLWindow("Madhat NeHe Template", 640, 480, 16, fullscreen))
	{
		return 0;									// Quit If Window Was Not Created
	}


	//Set drawing timer to 20 frame per second
	UINT timer = SetTimer(hWnd, 0, 50, (TIMERPROC)NULL);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;

}