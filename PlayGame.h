//External Libreries
#include "Gotoxy.h"			//Coords
#include "Ship.h"			//Creating a ship
#include "Shot.h"			//Creating shots
#include "Asteroid.h"		//Creating asteroids
#include "DrawLimit.h"		//Drawing limits

#include <conio.h>	//Key listener
#include <list>		//Lists

//CONST FOR CONTROLS
#define ESPACE 32
#define ESC	27

using namespace std;

//Prototype function
int playGame(int,int,class Menu &pause);

//Function
int playGame(int x, int y, Menu &pause) {
	//Creating the player: Init X-Y Coords, 5 "hearts", 5 "lives"
	Ship player(x,y,5,5);
	
	player.drawShip();			//Drawing the design of the player
	player.drawHeartsShip();	//Init draw hearts

	//Creating shots for the player
	list<Shot*> S;
	list<Shot*>::iterator it;

	//Creating the asteroids
	list<Asteroid*> A;
	list<Asteroid*>::iterator itA;
	
	bool game_over = false;							//Flag GAME OVER
	int pause_game = 1;								//Flag PAUSE GAME
	int level = pause.getLevel();					//Saving the level
	int difficult = pause.getDifficultIterator();	//Saving the difficult
	int game_status;
	int points = 0;									//Points as a variable
	
	switch (difficult) {
		case 0:	//EASY - 2 ASTEROID
				for(int i=0; i<2; i++) {
					//Generate the INIT asteroids in random positions between X = 75, and Y = 4
					A.push_back(new Asteroid(rand()%75 + 3, rand()%5 + 4));
				}
			break;
		case 1:	//NORMAL - 4 ASTEROIDS
				for(int i=0; i<4; i++) {
					//Generate the INIT asteroids in random positions between X = 75, and Y = 4
					A.push_back(new Asteroid(rand()%75 + 3, rand()%5 + 4));
				}
			break;
		case 2:	//HARD - 6 ASTEROIDS
				for(int i=0; i<6; i++) {
					//Generate the INIT asteroids in random positions between X = 75, and Y = 4
					A.push_back(new Asteroid(rand()%75 + 3, rand()%5 + 4));
				}
			break;
	}
	
	drawLimitGame();								//Drawing the limit
	
	while(!game_over) {
		gotoxy(4,2);	printf("Points: %d",points);			//Drawing points
		gotoxy(25,2);	printf("Level: %d",level);				//Print the current level
		
		//If a key is pressed
		if (kbhit()) {
			char key = getch();	//Get the keY
			
			//While we're playing we can shot
			if(key == ESPACE) {
				S.push_back(new Shot(player.getX()+2,player.getY()-1));	//Generate shot
			}
			
			//While we're playing we can pause, the two options are 'CONTINUE' and 'QUIT'
			if(key == ESC) {
				pause.drawPauseMenu();		//Drawing the pause menu while we're playing
				
				while(pause_game == 1) {
					game_status = pause.listenerPauseMenu();	//Runs the pause menu
					if (game_status == 2) {
						pause_game = game_status;	//pause_game = 2
					}
					if (game_status == 0) {
						pause_game = game_status;	//pause_game = 0
						game_over = true;
					}
				}
				if (game_status == 2) {
					pause_game = 1;				//Reboot default value
				}
				pause.ereasePauseMenu();		//Ereasing the pause menu
			}
		}
		
		//Running all the list for shots
		for (it = S.begin(); it != S.end(); it++) {
			(*it)->shottingShot();					//Draw the shot
			if ((*it)->limitShot()) {				//Erease the shot
				gotoxy((*it)->getX(), (*it)->getY());	printf(" ");
				delete(*it);
				it = S.erase(it);
			}
		}

		//Detect the player and the asteroid collision
		for(itA = A.begin(); itA != A.end(); itA++) {
			(*itA)->moveAsteroid();
			(*itA)->smashAsteroid(player);
		}
		
		//Shotting event, erease, create new asteroids and adds points
		for(itA = A.begin(); itA != A.end(); itA++) {
			for (it = S.begin(); it != S.end(); it++) {
				if( ((*itA)->getX() == (*it)->getX()) && (((*itA)->getY()+1 == (*it)->getY()) || ((*itA)->getY() == (*it)->getY()))) {
					gotoxy((*it)->getX(), (*it)->getY());	printf(" ");	//Erease shot
					delete(*it);											//Erease from list
					it = S.erase(it);										//Erease from list
					
					A.push_back(new Asteroid(rand()%75 + 3, rand()%5 + 4));	//Generates new asteroid
					gotoxy((*itA)->getX(), (*itA)->getY());	printf(" ");	//Erease asteroid
					delete(*itA);											//Erease from list
					itA = A.erase(itA);										//Erease from list
					
					points += 100;		//Adding points
				}
			}
		}
		
		player.moveShip();
		player.deadShip();
		
		//When you are between 1, 2 and 3 levels you need 1000 points
		if ((level == 1) || (level == 2) || (level == 3)) {
			if (points >= 100) {
				levelsMessage(level);
				level++;
				
				Sleep(3000);		//3 SECS
				gotoxy(2,28);		system("pause");	//Pause
				system("cls");							//Clear
				
				points = 0;								//Reset the points
				player.setHearts(5);					//Reset the hearts
				player.drawShip();						//Redrawing the player
				player.drawHeartsShip();				//Redrawing the hearts
				drawLimitGame();						//Redrawing the limits
			}
		}
		
		//When you are between 4, 5 and 6 levels you need 3000 points
		if ((level == 4) || (level == 5) || (level == 6)) {
			if (points >= 300) {
				levelsMessage(level);
				level++;
				
				Sleep(3000);		//3 SECS
				gotoxy(2,28);		system("pause");	//Pause
				system("cls");							//Clear
				
				points = 0;								//Reset the points
				player.setHearts(5);					//Reset the hearts
				player.drawShip();						//Redrawing the player
				player.drawHeartsShip();				//Redrawing the hearts
				drawLimitGame();						//Redrawing the limits
			}
		}
		
		//When you are between 7, 8 and 9 levels you need 5000 points
		if ((level == 7) || (level == 8) || (level == 9)) {
			if (points >= 500) {
				levelsMessage(level);
				level++;
				
				Sleep(3000);		//3 SECS
				gotoxy(2,28);		system("pause");	//Pause
				system("cls");							//Clear
				
				points = 0;								//Reset the points
				player.setHearts(5);					//Reset the hearts
				player.drawShip();						//Redrawing the player
				player.drawHeartsShip();				//Redrawing the hearts
				drawLimitGame();						//Redrawing the limits
			}
		}
		
		//When you are about to win you need 7000 points
		if (level == 10) {
			if (points >= 700) {
				levelsMessage(level);
				
				game_over = true;
				pause_game = 0;
				
				Sleep(3000);		//3 SECS
				gotoxy(2,28);		system("pause");	//Pause
				system("cls");							//Clear 
			}
		}
		
		if(player.getLives() == 0) { 
			game_over = true;
			pause_game = 0;
			
			player.ereaseShip();		//Ereasing player
			gameOverMessage();			//Game over message inside the box
			
			gotoxy(2,28);		system("pause");	//Pause
			system("cls");							//Clear 
		}	//Game Over
		
		Sleep(30);	//30 ms, rest CPU
	}
	return pause_game;
}
