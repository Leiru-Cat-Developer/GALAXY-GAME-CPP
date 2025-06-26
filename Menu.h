#ifndef MENU_H
#define MENU_H

//External libreries
#include "Gotoxy.h"			//Coords
#include "DrawLimit.h"		//Drawing limits

#include <stdio.h>		//Print letters
#include <conio.h>		//Key listener

//CONST FOR CONTROL
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ENTER 13

class Menu{
	private:
		//Variables
		int optionCoordY;
		int selectorCoordX;
		int selectorCoordY;
		int difficultIterator;
		int level;
	public:
		//Constructor
		Menu(int _optionCoordY, 
			 int _selectorCoordX,
			 int _selectorCoordY,
			 int _difficultIterator,
			 int _level): optionCoordY(_optionCoordY), 
									  selectorCoordX(_selectorCoordX),
									  selectorCoordY(_selectorCoordY),
									  difficultIterator(_difficultIterator),
									  level(_level) {}
		//Functions
		void drawMainMenu();
		void drawPauseMenu();
		void ereasePauseMenu();
		void drawOptionMenu();
		
		void drawDiffitultOptionMenu();
		void ereaseDrawDiffitultOptionMenu();
		
		void drawLevelOptionMenu();
		void ereaseLevelOptionMenu();
		
		void drawOptionArrow();
		void ereaseOptionArrow();
		
		int listenerMainMenu();
		bool listenerOptionMenu();
		int listenerPauseMenu();
		
		//Getters and Setters
		int getOptionCoordY() { return optionCoordY; }
		int getSelectorCoordX() { return selectorCoordX; }
		int getSelectorCoordY() { return selectorCoordY; }
		int getDifficultIterator() { return difficultIterator; }
		int getLevel() { return level; }
};

void Menu::drawMainMenu() {
	drawLimitMenu();			//External library
	
	drawOptionArrow();
	
	gotoxy(selectorCoordX,selectorCoordY);		printf("START GAME");
	gotoxy(selectorCoordX+2,selectorCoordY+2);	printf("OPTIONS");
	gotoxy(selectorCoordX+4,selectorCoordY+4);	printf("EXIT");
}

void Menu::drawPauseMenu() {
	drawOptionArrow();
	
	gotoxy(selectorCoordX+4,selectorCoordY);		printf("CONTINUE");
	gotoxy(selectorCoordX+6,selectorCoordY+2);		printf("QUIT");
}

void Menu::ereasePauseMenu() {
	ereaseOptionArrow();
	
	gotoxy(selectorCoordX,selectorCoordY);		printf("            ");
	gotoxy(selectorCoordX+2,selectorCoordY+2);	printf("            ");
}

void Menu::drawOptionMenu() {
	drawLimitMenu();			//External library
	
	drawDiffitultOptionMenu();	//Draw [easy - normal - hard]
	drawLevelOptionMenu();		//Draw [1 - 10]
	
	drawOptionArrow();
	
	gotoxy(selectorCoordX,selectorCoordY);		printf("DIFFICULT:");
	gotoxy(selectorCoordX+2,selectorCoordY+2);	printf("LEVEL:");
	gotoxy(selectorCoordX+4,selectorCoordY+4);	printf("RETURN");
}

void Menu::drawDiffitultOptionMenu() {
	switch(difficultIterator) {
		case 0:		gotoxy(selectorCoordX+12,selectorCoordY);		printf("EASY");
			break;
		case 1:		gotoxy(selectorCoordX+12,selectorCoordY);		printf("NORMAL");
			break;
		case 2:		gotoxy(selectorCoordX+12,selectorCoordY);		printf("HARD");
			break;
		default:	gotoxy(selectorCoordX+12,selectorCoordY);		printf("ERROR");
			break;
	}
}

void Menu::ereaseDrawDiffitultOptionMenu() {
	gotoxy(selectorCoordX+12,selectorCoordY);		printf("            ");
}

void Menu::drawLevelOptionMenu() {
	switch(level) {
		case 1:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("1");
			break;
		case 2:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("2");
			break;
		case 3:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("3");
			break;
		case 4:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("4");
			break;
		case 5:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("5");
			break;
		case 6:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("6");
			break;
		case 7:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("7");
			break;
		case 8:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("8");
			break;
		case 9:		gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("9");
			break;
		case 10:		gotoxy(selectorCoordX+12,selectorCoordY+2);	printf("10");
			break;
		default:	gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("ERROR");
			break;
	}
}

void Menu::ereaseLevelOptionMenu() {
	gotoxy(selectorCoordX+12,selectorCoordY+2);		printf("      ");
}

void Menu::drawOptionArrow() {
	gotoxy(selectorCoordX-4,optionCoordY);	printf("%c",175);
}

void Menu::ereaseOptionArrow() {
	gotoxy(selectorCoordX-4,optionCoordY);	printf(" ");
}

int Menu::listenerMainMenu() {
	bool end_menu = false;
	
	//If a key is pressed
	if (kbhit()) {
		char key = getch();		//Get the key
		ereaseOptionArrow();	//We erease the last option
		
		//We check the key and the limit of the selection
		if(key == UP && optionCoordY > selectorCoordY) optionCoordY-=2;		//Up
		if(key == DOWN && optionCoordY < selectorCoordY+4) optionCoordY+=2;	//Down
		
		//When we chose an option
		if(key == ENTER) {
			if (optionCoordY == selectorCoordY) {			//START GAME (OP1)
				/*
					We return a number 2, which means we are going
					to start the game. The conditional in DrawMenu.h
					has a conditional for this
				*/
				return 2;
			}
			if (optionCoordY == selectorCoordY+2) {			//OPTIONS (OP2)
				optionCoordY = selectorCoordY;	//We restart the coords of the selector
				system("cls");					//We clean the screen to show the new option menu
				drawOptionMenu();				//We print the option menu
				
				//We start a new cicle with another menu option function inside
				while(!end_menu) {
					end_menu = listenerOptionMenu(); //Returns true or false, it depends the option choiced
				}
				drawMainMenu();	//When the cicle ends, we re-draw the main menu
			}
			if (optionCoordY == selectorCoordY+4) {			//EXIT (OP3)
				/*
					We return a 0 which means the conditional in
					DrawMenu.h is going to consider it as a finish
				*/
				return 0;
			}
		}
		drawOptionArrow();	//We draw the new option
	}
	return 1;	//1 means is going to repeat the cicle
}

bool Menu::listenerOptionMenu() {	
	//If a key is pressed
	if (kbhit()) {
		char key = getch();		//Get the key
		ereaseOptionArrow();	//We erease the last option
		
		//We check the key and the limit
		if(key == UP && optionCoordY > selectorCoordY) optionCoordY-=2;		//Up
		if(key == DOWN && optionCoordY < selectorCoordY+4) optionCoordY+=2;	//Down
		
		//The same coords in difficult option, allowed us to move left or right
		if (optionCoordY == selectorCoordY) {						//DIFFICULT (OP4)
			if(key == LEFT) {
				if (difficultIterator >= 0) {
					difficultIterator--;								//Rest 1
					if (difficultIterator < 0) { difficultIterator++; }	//If we have -1
					ereaseDrawDiffitultOptionMenu();					//Erease current difficult
					drawDiffitultOptionMenu();							//Draw new difficult
				}
			}//Left
			
			if(key == RIGHT) {
				if (difficultIterator <= 2) {
					difficultIterator++;								//Add 1
					if (difficultIterator > 2) { difficultIterator--; }	//If we have 3
					ereaseDrawDiffitultOptionMenu();					//Erease current difficult
					drawDiffitultOptionMenu();							//Draw new difficult
				}
			}//Right
		}
		
		//If is in the same coords at level option, allowed us to move left or right
		if (optionCoordY == selectorCoordY+2) {						//LEVEL (OP5)
			if(key == LEFT) {
				if (level >= 1) {
					level--;					//Rest 1
					if (level < 1) { level++; }	//If we have 0
					ereaseLevelOptionMenu();	//Erease current level
					drawLevelOptionMenu();		//Draw new level
				}
			}//Left
			
			if(key == RIGHT) {
				if (level <= 10) {
					level++;					//Add 1
					if (level > 10) { level--; }//If we have 11
					ereaseLevelOptionMenu();	//Erease current level
					drawLevelOptionMenu();		//Draw new level
				}
			}//Right
		}
		
		//Last option function
		if((key == ENTER) && (optionCoordY == selectorCoordY+4)) {	//RETURN (OP6)					
			optionCoordY = selectorCoordY;	//Restart the coords of the selector
			system("cls");					//We clean the screen to restart the menu
			return true;					//We end this function sending a true
		}
		drawOptionArrow();	//We draw the new option
	}
}

int Menu::listenerPauseMenu() {
	//If a key is pressed
	if (kbhit()) {
		char key = getch();		//Get the key
		ereaseOptionArrow();	//We erease the last option
		
		//We check the key and the limit of the selection
		if(key == UP && optionCoordY > selectorCoordY) optionCoordY-=2;		//Up
		if(key == DOWN && optionCoordY < selectorCoordY+2) optionCoordY+=2;	//Down
		
		//When we chose an option
		if(key == ENTER) {
			if (optionCoordY == selectorCoordY) {				//CONTINUE (OP7)
				return 2;
			}
			if (optionCoordY == selectorCoordY+2) {				//QUIT (OP8)
				return 0;
			}
		}
		drawOptionArrow();	//We draw the new option
	}
	return 1;	//Continues the cicle
}
#endif
