#ifndef SHIP_H
#define SHIP_H

//External Libreries
#include "Gotoxy.h"		//Coords

#include <stdio.h>		//Print letters
#include <conio.h>		//Key listener

//CONST FOR CONTROLS
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

//Class
class Ship{
	private:
		int coordX;
		int coordY;
		int hearts;
		int lives;
	public:
		//Simple constructor
		Ship(int _coordX,
		     int _coordY,
			 int _hearts,
			 int _lives): coordX(_coordX),
			              coordY(_coordY),
						  hearts(_hearts),
						  lives(_lives) {}
		
		//Functions
		void drawShip();
		void ereaseShip();
		void moveShip();
		void drawHeartsShip();
		void decreaseHeartsShip() { hearts--; }
		void deadShip();
		
		//Getters and Setters
		int getX() { return coordX; }
		int getY() { return coordY; }
		int getLives() { return lives; }
		
		void setHearts(int new_hearts) { hearts = new_hearts; }
};

void Ship::drawShip() {
	gotoxy(coordX,coordY);		printf("  %c",186);
	gotoxy(coordX,coordY+1);	printf("%c%c%c%c%c",186,201,206,187,186);
	gotoxy(coordX,coordY+2);	printf("%c%c%c%c%c",200,219,202,219,188);
}

void Ship::ereaseShip() {
	gotoxy(coordX,coordY);		printf("     ");
	gotoxy(coordX,coordY+1);	printf("     ");
	gotoxy(coordX,coordY+2);	printf("     ");
}

void Ship::moveShip() {
	//If a key is pressed
	if (kbhit()) {
		char key = getch();	//Get the key
		
		//Position and cleaning the residue
		ereaseShip();
		
		//We check the key and the limit
		if(key == UP && coordY > 6) coordY--;		//Up
		if(key == LEFT && coordX > 3) coordX--;		//Left
		if(key == DOWN && coordY+3 < 23) coordY++;	//Down
		if(key == RIGHT && coordX+6 < 78) coordX++;	//Right
		
		//Position and printing the character
		drawShip();
		
		//Update hearts quantity
		drawHeartsShip();
	}
}

void Ship::drawHeartsShip() {
	gotoxy(50,2);	printf("Lives: %d",lives);
	gotoxy(64,2);	printf("Life: ");
	gotoxy(70,2);	printf("      ");
	for(int i=0; i<hearts; i++){
		gotoxy(70+i,2);	printf("%c",3);
	}
}

void Ship::deadShip() {
	if (hearts == 0) {
		//First part of the animation
		ereaseShip();	//Erease the ship
		gotoxy(coordX,coordY);		printf("  *  ");
		gotoxy(coordX,coordY+1);	printf("* * *");
		gotoxy(coordX,coordY+2);	printf("  *  ");
		Sleep(300);	//Wait to show the animation
		
		//Second part of the animation
		ereaseShip();	//Erease the ship
		gotoxy(coordX,coordY);		printf(" *** ");
		gotoxy(coordX,coordY+1);	printf("* * *");
		gotoxy(coordX,coordY+2);	printf(" *** ");
		Sleep(300);	//Wait to show the animation
		
		//Third part of the animation
		ereaseShip();	//Erease the ship
		gotoxy(coordX,coordY);		printf("*   *");
		gotoxy(coordX,coordY+1);	printf("  *  ");
		gotoxy(coordX,coordY+2);	printf("*   *");
		Sleep(300);	//Wait to show the animation
		
		//Restart
		hearts = 5;
		lives--;
		ereaseShip();
		drawShip();
		drawHeartsShip();
	}
}
#endif
