#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include "../breakout/include/base.h"

#define WINDOW_HEIGHT 1280.0f
#define WINDOW_WIDTH 720.0f

typedef enum{
	START_MENU,
	RUNNING_MENU,
	DEFEAT_MENU,
	VICTORY_MENU
}GameState;

typedef struct{
	i16 radius;
	Vector2 pos;
}Player;



int main(){

	InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"idk tbh, something two players can play ig");

	Player p1 =
	{
		.radius = 20,
		.pos = {WINDOW_WIDTH/2.0f, WINDOW_HEIGHT/2.0f}
	};

	while(!WindowShouldClose){
		ClearBackground(BLACK);
		DrawCircle(p1.pos.x, p1.pos.y, p1.radius, RED);
	


	};
	CloseWindow();
	return 0;
}

