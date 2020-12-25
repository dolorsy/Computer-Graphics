#ifndef ROOM_CPP
#define ROOM_CPP
#include <windows.h>		
#include"tools.cpp"
#include <gl\gl.h>			
#include <gl\glu.h>			
#include "Manager.cpp"
class Room :public Shape{
private:
	double width, length, height;
	GLuint wall, door;
public:
	vector<_3D_double>allPoints;
	Room(Shape*parent, _3D_double center, _3D_double length, GLuint wall,GLuint door,GLuint carpet) :Shape(parent, center, length){
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//A 0
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//B 1
 		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//C 2
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//D 3 
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() + length.getZ() / 2));//E 4
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() + length.getZ() / 2));//F 5
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() + length.getZ() / 2));//G 6 
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() + length.getZ() / 2));//H 7
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 4, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//I 8
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 4, center.getY() + length.getY() / 4, center.getZ() - length.getZ() / 2));//J 9
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 4, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//K 10 
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 4, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//L 11
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 4, center.getY() + length.getY() / 4, center.getZ() - length.getZ() / 2));//M 12
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 4, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//N 13
		allPoints.push_back(_3D_double(center.getX(), center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//O 14
		allPoints.push_back(_3D_double(center.getX() , center.getY() + length.getY() /4, center.getZ() - length.getZ() / 2));//P 15

		this->wall = wall;
		this->door = door;
		
	}
	void drawShape(){
		tools::drawRoom(allPoints,wall);
		//left door
		//todo controlling the door by move() method
		tools::drawDoor(allPoints[8],allPoints[9],allPoints[15],allPoints[14], door);
		//right door
		//todo controlling the door by move() method
		tools::drawDoor(allPoints[14], allPoints[15], allPoints[12], allPoints[13], door);
		
	}

	vector<_3D_double> getAllPoints(){
		return allPoints;
	}

};
#endif