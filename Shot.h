#ifndef SHOT_H
#define SHOT_H

//External libreries
#include "Gotoxy.h"		//Coords

#include <stdio.h> 		//Print letter

class Shot {
	private:
		int coordX;
		int coordY;
	public:
		Shot(int _coordX,
		     int _coordY): coordX(_coordX),
			 			   coordY(_coordY) {}
			 			   
		void shottingShot();
		bool limitShot();
		
		//Getters and Setters
		int getX() { return coordX; }
		int getY() { return coordY; }
};

void Shot::shottingShot() {
	gotoxy(coordX,coordY);	printf(" ");
	coordY--;
	gotoxy(coordX,coordY);	printf("%c",221);
}

bool Shot::limitShot() {
	if(coordY ==  4) return true;
	return false;
}
#endif
