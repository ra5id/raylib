#include <stdio.h>
#include <raylib.h>
#include <stdbool.h>
#include "../breakout/include/base.h"

#define WINDOW_HEIGHT 720.0f
#define WINDOW_WIDTH 1280.0f

#define BOUNDARY_WIDTH 5.0f
#define BOUNDARY_COLLISION_OFFSET 2.5f
#define P1_RADIUS 20.0f
#define P2_RADIUS 20.0f

#define LEFT_SIDE_WINDOW_CENTER_X 320.0f
#define RIGHT_SIDE_WINDOW_CENTER_X 960.0f

#define PLAYER_SPEED 500.0f

typedef enum{
	START_MENU_STATE,
	PLAYING_STATE,
	DEFEAT_MENU_STATE,
	VICTORY_MENU_STATE
}GameState;

typedef struct{
	i16 radius;
	Vector2 pos;
}Player;

typedef struct{
	i16 radius;
	Vector2 pos;
}Button;

void update_player(Player *p1, Player *p2, Rectangle *boundary)
{
	f32 dt; dt = GetFrameTime();
	
	if(IsKeyDown(KEY_W)){
		p1->pos.y -= PLAYER_SPEED * dt;
	}
	if(IsKeyDown(KEY_S)){
		p1->pos.y += PLAYER_SPEED * dt;
	}
	if(IsKeyDown(KEY_A)){
		p1->pos.x -= PLAYER_SPEED * dt;
	}
	if(IsKeyDown(KEY_D)){
		p1->pos.x += PLAYER_SPEED * dt;
	}
	
	if(IsKeyDown(KEY_UP)){
		p2->pos.y -= PLAYER_SPEED * dt;
  }	
	if(IsKeyDown(KEY_DOWN)){
		p2->pos.y += PLAYER_SPEED * dt;
	}
	if(IsKeyDown(KEY_LEFT)){
		p2->pos.x -= PLAYER_SPEED * dt;
	}
	if(IsKeyDown(KEY_RIGHT)){
		p2->pos.x += PLAYER_SPEED * dt;
	}
		
	if(p1->pos.x < p1->radius){
		p1->pos.x = p1->radius;
	}
	if(p1->pos.y < p1->radius){
		p1->pos.y = p1->radius;
	}
	if(p1->pos.x > WINDOW_WIDTH-p1->radius){
		p1->pos.x = WINDOW_WIDTH-p1->radius;	
	}
	if(p1->pos.y > WINDOW_HEIGHT-p1->radius){
		p1->pos.y = WINDOW_HEIGHT-p1->radius;	
	}
	if(p2->pos.x < p2->radius){
		p2->pos.x = p2->radius;
	}
	if(p2->pos.y < p2->radius){
		p2->pos.y = p2->radius;
	}
	if(p2->pos.x > WINDOW_WIDTH-p2->radius){
		p2->pos.x = WINDOW_WIDTH-p2->radius;	
	}
	if(p2->pos.y > WINDOW_HEIGHT-p2->radius){
		p2->pos.y = WINDOW_HEIGHT-p2->radius;	
	}
  
	bool boundry_collision_p1 = 
	{
		CheckCollisionCircleRec(p1->pos, p1->radius,*boundary)
	};
	bool boundry_collision_p2 = 
	{
		CheckCollisionCircleRec(p2->pos, p2->radius,*boundary)
	};

	if(boundry_collision_p1){
		p1->pos.x = WINDOW_WIDTH/2 - (p1->radius + BOUNDARY_COLLISION_OFFSET);
	}
	if(boundry_collision_p2){
		p2->pos.x = WINDOW_WIDTH/2 + (p2->radius + BOUNDARY_COLLISION_OFFSET);
	}
}

int main()
{

	InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"idk tbh, something two players can play ig");

	
	Player p1 =
	{
		.radius = P1_RADIUS,
		.pos = {LEFT_SIDE_WINDOW_CENTER_X, WINDOW_HEIGHT/2.0f}
	};
	Player p2 =
	{
		.radius = P2_RADIUS,
		.pos = {RIGHT_SIDE_WINDOW_CENTER_X, WINDOW_HEIGHT/2.0f}
	};

	Rectangle boundary = 
	{
		WINDOW_WIDTH/2.0f - BOUNDARY_WIDTH / 2.0f,
		0.0f,
		BOUNDARY_WIDTH,
		WINDOW_HEIGHT
	};
		
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
	
    GameState Game = PLAYING_STATE;

	if(PLAYING_STATE){
		update_player(&p1, &p2, &boundary);

		DrawCircleV(p1.pos, p1.radius,GREEN);
		DrawCircleV(p2.pos, p2.radius,RED);
    
		DrawRectangleRec(boundary,RED);
	}

		EndDrawing();
	};

	CloseWindow();
	return 0;
}

