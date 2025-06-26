#ifndef GOTOXY_H
#define GOTOXY_H

#include <windows.h>	//GOTOXY and Hide cursor

//Prototype functions
void gotoxy(int,int);
void hideCursor();

//Functions
void gotoxy(int x,int y) {
	//Ask for console ID
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//Ask for coords, X and Y
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	
	//Set cursor position
	SetConsoleCursorPosition(hCon,dwPos);
}

void hideCursor() {
	//Ask for the console ID
	HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	
	//Ask for cursor set up
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;			//0 - 100 Size
	cci.bVisible = FALSE;	//TRUE or FALSE
	
	//Set up cursor, CCI with reference
	SetConsoleCursorInfo(hCon, &cci);
}
#endif
