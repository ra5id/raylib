#include "phy.h"
#include "base.h"
#include <stdio.h>
#include <raylib.h>

int main(){

	InitWindow(WINDOW_W, WINDOW_H, "breakout");
	SetTargetFPS(60);
	while(WindowShouldClose()){
	
		drawing_stuff();
	}

	CloseWindow();
	return 0;
}

