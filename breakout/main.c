#include "phy.h"
#include "base.h"
#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>

int main(){

	Vec2 Cvel = {200,200};
	Vec2 Cpos = {WINDOW_W/2.0f, WINDOW_H/2.0f};


	Paddle p = {
		.rect = {
			WINDOW_W/2.0f-50,
			WINDOW_H-12.0f,
			100.0f,
			8.0f},
		
		.vel = 0
	};
	 	
	InitWindow(WINDOW_W, WINDOW_H, "breakout");
	SetTargetFPS(60);

	while(!WindowShouldClose()){

		check_gameover(&Cpos);
		Update_ball(&Cpos, &Cvel, &p);
		Update_paddle(&p);
		drawing_stuff(&Cpos, &p.rect);
		
	

	}
	
	CloseWindow();
	return 0;
}

