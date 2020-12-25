#ifndef ROOF_CPP
#define ROOF_CPP
#include <windows.h>		
#include"tools.cpp"
#include <gl\gl.h>			
#include <gl\glu.h>			
#include "Manager.cpp"
#include "Room.cpp"

class Roof :public Shape{
private:
	vector<_3D_double> allPoints;
	GLuint roofWall, door, carpet;
public:
	Roof(Shape* parent, _3D_double center, _3D_double length, GLuint roofWall, GLuint door, GLuint carpet) :Shape(parent, center, length){
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//A 0
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//B 1
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() - length.getZ() / 2));//C 2
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() - length.getZ() / 2));//D 3 
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() + length.getZ() / 2));//E 4
		allPoints.push_back(_3D_double(center.getX() - length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() + length.getZ() / 2));//F 5
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() + length.getY() / 2, center.getZ() + length.getZ() / 2));//G 6 
		allPoints.push_back(_3D_double(center.getX() + length.getX() / 2, center.getY() - length.getY() / 2, center.getZ() + length.getZ() / 2));//H 7	
		this->roofWall = roofWall;
		this->door = door;
		this->carpet = carpet;
		
		Room* room1;
		room1 = new Room(this, _3D_double(this->center.getX() + length.getX() / 4, center.getY(), center.getZ() + length.getZ() / 4),
			_3D_double(length.getX() / 2, length.getY(), length.getZ() / 2), roofWall, door, carpet);
	}
	void drawShape(){
		//back side
		tools::drawSide(allPoints[4], allPoints[5], allPoints[6], allPoints[7],roofWall );

		//right side
		tools::drawSide(allPoints[3], allPoints[2], allPoints[6], allPoints[7],roofWall );
		//left side
		tools::drawSide(allPoints[0], allPoints[1], allPoints[5], allPoints[4], roofWall);
		//up side
		tools::drawSide(allPoints[1], allPoints[5], allPoints[6], allPoints[2],roofWall);
		//bottom side
		tools::drawSide(allPoints[0], allPoints[4], allPoints[7], allPoints[3], roofWall);

		//front face
		tools::drawSide(allPoints[0], allPoints[1], allPoints[2], allPoints[3],roofWall);
	}
	vector<_3D_double> getAllPoints(){
		return allPoints;
	}
};


#endif