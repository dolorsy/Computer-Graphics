#ifndef AIRCRAFT_CPP
#define AIRCRAFT_CPP
#include "Manager.cpp"
#include <Model_3DS.h>


class AirCraft{
private:
	double angel;
	_3D_double position;
	Model_3DS *swing;
public:
	AirCraft(){
		swing = new Model_3DS();
swing->Load("Airplane.3ds");
GLTexture swing0, swing1, swing2, swing3, swing4, swing5, swing7;
swing0.LoadBMP((char*)"photo3d.bmp");
swing1.LoadBMP((char*)"photo3d.bmp");
swing->Materials[0].tex = swing0;
swing->Materials[1].tex = swing1;
angel = 0; 
swing->pos.x = position.getX();
swing->pos.y = position.getY();
swing->pos.z = position.getZ();

	}
	AirCraft(_3D_double position){
		AirCraft();
		this->position = position;
	}
	AirCraft(int x, int y , int z){
				AirCraft();
		this->position.setX(x) ;
		this->position.setY(y);
		this->position.setZ( z);
	}
	void DrawCraft();
	

};

void AirCraft::DrawCraft(){
	angel++;
	glPushMatrix();
	glRotatef(angel*7,0,1,0);
	glTranslatef(10,10,0);
	glScalef(0.05,0.05,0.05);
	glRotatef(180,0,1,0);
	
	swing->Draw();

	glPopMatrix();
}
#endif