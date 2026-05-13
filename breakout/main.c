#include "phy.h"
#include "base.h"
#include <stdio.h>
#include <raylib.h>

typedef struct{
	i32 x;
	i32 y;
	i32 width;
	i32 height;
} BaseRect;

int main(){

	const Vec2 Cvel = {500,500};

	Vec2 Cpos = {WINDOW_W/2.0f, WINDOW_H/2.0f};
	
	InitWindow(WINDOW_W, WINDOW_H, "breakout");
	SetTargetFPS(60);

	
	while(!WindowShouldClose()){

		Update_movement(&Cpos, &Cvel);	
		drawing_stuff(&Cpos);
		
		}
	
	CloseWindow();
	return 0;
}

