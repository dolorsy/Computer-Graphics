#ifndef TOOLS_H
#define TOOLS_H
#include <windows.h>	// Header File For Windows
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <math.h>
//#include <texture.h>
#include <iostream>
#include "Manager.cpp"
struct tools{
static void drawSide(_3D_double vertixA, _3D_double vertixB, _3D_double vertixC, _3D_double vertixD, unsigned int tex){
	
	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(vertixA.getX(), vertixA.getY(), vertixA.getZ());
	glTexCoord2d(0, 3);
	glVertex3d(vertixB.getX(), vertixB.getY(), vertixB.getZ());
	glTexCoord2d(3, 3);
	glVertex3d(vertixC.getX(), vertixC.getY(), vertixC.getZ());
	glTexCoord2d(3, 0);
	glVertex3d(vertixD.getX(), vertixD.getY(), vertixD.getZ());
	glEnd();
}

static void drawDoor(_3D_double vertixA, _3D_double vertixB, _3D_double vertixC, _3D_double vertixD, unsigned int tex){
	glBindTexture(GL_TEXTURE_2D, tex);

	glBegin(GL_QUADS);
	glTexCoord2d(0, 0);
	glVertex3d(vertixA.getX(), vertixA.getY(), vertixA.getZ());
	glTexCoord2d(0, 1);
	glVertex3d(vertixB.getX(), vertixB.getY(), vertixB.getZ());
	glTexCoord2d(1, 1);
	glVertex3d(vertixC.getX(), vertixC.getY(), vertixC.getZ());
	glTexCoord2d(1, 0);
	glVertex3d(vertixD.getX(), vertixD.getY(), vertixD.getZ());
	glEnd();
}

static void drawRoom(vector<_3D_double>&allPoints,GLuint wall){

	//back side
	drawSide(allPoints[4], allPoints[5], allPoints[6], allPoints[7], wall);

	//right side
	drawSide(allPoints[3], allPoints[2], allPoints[6], allPoints[7], wall);
	//left side
	drawSide(allPoints[0], allPoints[1], allPoints[5], allPoints[4], wall);
	//up side
	drawSide(allPoints[1], allPoints[5], allPoints[6], allPoints[2], wall);
	//bottom side

	drawSide(allPoints[0], allPoints[4], allPoints[7], allPoints[3], wall);
	//front face
	//first part
	drawSide(allPoints[0], allPoints[1], allPoints[10], allPoints[8], wall);

	//second part
	drawSide(allPoints[9], allPoints[10], allPoints[11], allPoints[12], wall);

	//third part	
	drawSide(allPoints[13], allPoints[11], allPoints[2], allPoints[3], wall);

}
static void drawClosed(vector<_3D_double>&allPoints,GLuint wall){
		drawSide(allPoints[0], allPoints[1], allPoints[2], allPoints[3], wall);
	drawSide(allPoints[4], allPoints[5], allPoints[6], allPoints[7], wall);
	drawSide(allPoints[0], allPoints[1], allPoints[5], allPoints[4], wall);
	drawSide(allPoints[1], allPoints[5], allPoints[6], allPoints[2], wall);

}

};
#endif
