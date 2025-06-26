#ifndef ASTEROID_H
#define ASTEROID_H

//External Libreries
#include "Gotoxy.h"		//Coords
#include "Ship.h"		//Creating a ship

#include <stdio.h>		//Print letters
#include <stdlib.h>		//Random generator

class Asteroid{
	private:
		int coordX;
		int coordY;
	public:
		//Simple constructor
		Asteroid(int _coordX,
				 int _coordY): coordX(_coordX),
				 			   coordY(_coordY) {}
		
		//Functions
		void drawAsteroid();
		void moveAsteroid();
		void smashAsteroid(class Ship &S);
		
		//Getters and Setters
		int getX() { return coordX; }
		int getY() { return coordY; }
};

void Asteroid::drawAsteroid() {
	gotoxy(coordX,coordY);	printf("o");
}

void Asteroid::moveAsteroid() {
	gotoxy(coordX,coordY);	printf(" ");
	coordY++;
	
	//Max limit coord
	if (coordY > 22) {
		coordX = rand()%71 + 5;
		coordY = 4;
	}
	drawAsteroid();
}

void Asteroid::smashAsteroid(class Ship &S) {
	//Definition of the limits of the colitions of the ship with the asteroid
	if ((coordX >= S.getX()) && (coordX < S.getX()+7) && (coordY >= S.getY()) && (coordY < S.getY()+2)) {
		S.decreaseHeartsShip();		//Rest hearts
		S.ereaseShip();				//To avoid the draw asteroids
		S.drawShip();				//Re-draw the ship
		S.drawHeartsShip();			//Re-draw hearts
		
		coordX = rand()%71 + 5;		//Random new position for asteroid
		coordY = 4;					//Limit start of the new position for the asteroid
	}
}
#endif
