//External libreries
#include "Menu.h"			//Menu Listeners
#include "PlayGame.h"		//Playing game

#include <stdio.h>	//Print letters

//Prototype function
void mainMenu();

//Function
void mainMenu() {
	/* 
		Option posY, X pos, Y pos [Init values]
		Difficult [0,1,2]
			0 = easy
			1 = normal
			2 = hard
		Level [1-10]
	*/
	
	Menu main(26,32,26,1,1);
	
	/*
		GAME STATUS for LISTENER MAIN MENU
		
		0 = End Program
		1 = Continue
		2 = Start Game
	*/
	
	/*
		GAME OPTIONS for PLAY GAME
		
		0 = End Play Game
		1 = Continue
	*/
	
	bool playing = false;		//Starts a bucle
	int game_status;			//To decide what are we going to do
	int main_options = 1;		//Main: Menu Options, while you're setting up
	int game_options = 1;		//Options: Menu Options, while you're playing
	
	while(!playing) {
		if (main_options == 1) {
			main.drawMainMenu();		//Drawing main menu INIT
			while(main_options == 1) {
				game_status = main.listenerMainMenu();										//Returns numbers, it depends the GAME STATUS
				if (game_status == 0 || game_status == 2) { main_options = game_status; }	//Both [0 or 2] we are going to break the cicle
			}	
		}
		
		//Creating the pause menu with the same values as main menu
		Menu pause(main.getOptionCoordY(),
				   main.getSelectorCoordX(),
				   main.getSelectorCoordY(),
				   main.getDifficultIterator(),
				   main.getLevel());
		
		system("cls");	//Clear Screen
		
		//Starting the game if game_status equals 2, if not, we just end the program
		if (game_status == 2) {
			while(game_options == 1) {
				game_options = playGame(38,20,pause);
			}
		}
		
		if (game_status == 0) {
			playing = true;			//playing = true, this ends the program
		}
		if (game_status == 2) {
			system("cls");
			main_options = 1;		//Reboot the main menu status
			game_options = 1;		//Reboot the options menu status
		}
	}
}
