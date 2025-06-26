//External libreries
#include "Gotoxy.h"			//Hidding the cursor
#include "DrawMenu.h"		//Drawing menu

int main(int argc, char** argv) {
	system("chcp 437 > nul");	//Code for ASCII problems
	
	hideCursor();	//Hidding the cursor
	mainMenu();		//Starting the main menu
	
	system("cls");	//Clear Screen, before end the game
	return 0;
}
