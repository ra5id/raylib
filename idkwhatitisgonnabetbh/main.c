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


typedef enum{
	START_MENU_STATE,
	PLAYING_STATE,
	DEFEAT_MENU_STATE,
	VICTORY_MENU_STATE
}GameState;

typedef struct{
	f32 radius;
	Vector2 pos;
	Vector2 vel;
}Player;

typedef struct{
	i16 radius;
	Vector2 pos;
}Button;

void update_player(Player *p1, Player *p2, Rectangle *boundary)
{
	f32 dt; dt = GetFrameTime();
	
	if(IsKeyDown(KEY_W)){
		p1->pos.y -= p1->vel.y * dt;
	}
	if(IsKeyDown(KEY_S)){
		p1->pos.y += p1->vel.y * dt;
	}
	if(IsKeyDown(KEY_A)){
		p1->pos.x -= p1->vel.x * dt;
	}
	if(IsKeyDown(KEY_D)){
		p1->pos.x += p1->vel.x * dt;
	}
	
	if(IsKeyDown(KEY_UP)){
		p2->pos.y -= p2->vel.y * dt;
  }	
	if(IsKeyDown(KEY_DOWN)){
		p2->pos.y += p2->vel.y * dt;
	}
	if(IsKeyDown(KEY_LEFT)){
		p2->pos.x -= p2->vel.x * dt;
	}
	if(IsKeyDown(KEY_RIGHT)){
		p2->pos.x += p2->vel.x * dt;
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

void level_one(Button *b1, Button *b2, Player *p1, Player *p2, Rectangle *pl, Rectangle *pr, GameState *Game)
{
	bool pleft_collision_check =
	{
		CheckCollisionCircleRec(p1->pos,p1->radius,*pl)
	};
	
	bool pright_collision_check =
	{
		CheckCollisionCircleRec(p2->pos,p2->radius,*pr)
	};

	if(pleft_collision_check){
		if(p1->pos.y-p1->radius < pl->y){
			p1->pos.y = pl->y-p1->radius;
		}
	}
	
	if(pright_collision_check){
		if(p2->pos.y-p2->radius < pr->y){
			p2->pos.y = pr->y-p2->radius;
		}
	}

	bool p1_button_collision = 
	{
		CheckCollisionCircles(b1->pos, b1->radius,p1->pos,p1->radius)
	};
	
	bool p2_button_collision = 
	{
		CheckCollisionCircles(b2->pos, b2->radius,p2->pos,p2->radius)
	};
	DrawRectangleRec(*pr,RED);
	DrawRectangleRec(*pl,GREEN);
	if(p1_button_collision && p2_button_collision){
		*Game = VICTORY_MENU_STATE;	
	}
}

int main()
{

	InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"idk tbh, something two players can play ig");

	
	Player p1 =
	{
		.radius = P1_RADIUS,
		.pos = {LEFT_SIDE_WINDOW_CENTER_X, WINDOW_HEIGHT/2.0f},
		.vel = {500.0f,500.0f}
	};
	Player p2 =
	{
		.radius = P2_RADIUS,
		.pos = {RIGHT_SIDE_WINDOW_CENTER_X, WINDOW_HEIGHT/2.0f},
		.vel = {500.0f, 500.0f}
	};

	Rectangle boundary = 
	{
		WINDOW_WIDTH/2.0f - BOUNDARY_WIDTH / 2.0f,
		0.0f,
		BOUNDARY_WIDTH,
		WINDOW_HEIGHT
	};

	Button b1 = {
		50.0f ,
		{60.0f, 60.0f}
	};
	
	Button b2 = {
		50.0f ,
		{1220.0f, 660.0f}
	};

	Rectangle pressure_plate_rightside = 
	{
		RIGHT_SIDE_WINDOW_CENTER_X-50+BOUNDARY_COLLISION_OFFSET,
		WINDOW_HEIGHT-20,
		100,
		20
	};
	
	Rectangle pressure_plate_leftside = 
	{
		LEFT_SIDE_WINDOW_CENTER_X-50-BOUNDARY_COLLISION_OFFSET,
		WINDOW_HEIGHT-20,
		100,
		20	
	};
	
  GameState Game = PLAYING_STATE;
		
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
	
	switch(Game)
	{
		case PLAYING_STATE:
			update_player(&p1, &p2, &boundary);
			level_one(&b1,&b2,&p1,&p2,&pressure_plate_leftside,&pressure_plate_rightside,&Game);

			DrawCircleV(b1.pos, b1.radius,RED);
			DrawCircleV(b2.pos, b2.radius,GREEN);
			
			DrawCircleV(p1.pos, p1.radius,GREEN);
			DrawCircleV(p2.pos, p2.radius,RED);
			
			DrawRectangleRec(boundary,YELLOW);	
			
			break;

		case VICTORY_MENU_STATE:
			i32 text1_size = MeasureText("YOU WIN", 50);
			DrawText("YOU WIN!", WINDOW_WIDTH/2-text1_size/2,WINDOW_HEIGHT/2-25,50,WHITE);	
			break;

	}

		EndDrawing();
	};

	CloseWindow();
	return 0;
}

