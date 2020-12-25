#ifndef CLOSEDBUILDING_CPP
#define CLOSEDBUILDING_CPP
#include <windows.h>		
#include"tools.cpp"
#include <gl\gl.h>			
#include <gl\glu.h>			
#include "Manager.cpp"
class NormalBuilding:public Shape{
private:
	double width, length, height;
	GLuint wall, door;
public:
	vector<_3D_double>allPoints;
	NormalBuilding(Shape*parent, _3D_double center, _3D_double length, GLuint wall,GLuint door,GLuint carpet) :Shape(parent, center, length){
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//A 0
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//B 1
 		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//C 2
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//D 3 
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() + length.getZ() / 2));//E 4
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() + length.getZ() / 2));//F 5
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() + length.getZ() / 2));//G 6 
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() + length.getZ() / 2));//H 7
		//allPoints.push_back(_3D_double(center.getX(), center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//O 14

		this->wall = wall;
		this->door = door;
		
	}
	void drawShape(){
		tools::drawClosed(allPoints,wall);
		//left door
		//todo controlling the door by move() method
		//tools::drawDoor(allPoints[8],allPoints[9],allPoints[15],allPoints[14], door);
		//right door
		//todo controlling the door by move() method
	//	tools::drawDoor(allPoints[14], allPoints[15], allPoints[12], allPoints[13], door);
		
	}

	vector<_3D_double> getAllPoints(){
		return allPoints;
	}

};
#endif