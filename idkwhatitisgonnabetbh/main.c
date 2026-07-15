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

#define MAX_BULLETS 100

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
	Color color; 
}Player;

typedef struct{
	f32 radius;
	Vector2 pos;
	Color color; 
}Button;

typedef struct{
	f32 radius;
	Vector2 pos;
	Vector2 vel;
	Color color; 
	bool active;
}Bullets;

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

void level_one(Button *b1, Button *b2, Player *p1, Player *p2, Rectangle *pl, Rectangle *pr, Bullets *bullet1,Bullets *bullet2, GameState *Game)
{
	f32 dt = GetFrameTime();
	
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
	
	for(int i = 0; i< MAX_BULLETS; i++){
		if(IsKeyPressed(KEY_SPACE)){
			if(!bullet1[i].active){
				bullet1[i].active = true;
				bullet1[i].pos = p1->pos;
				bullet1[i].vel = (Vector2){0.0f,1500.0f};
				break;
			}

		}
		if(bullet1[i].active){
			bullet1[i].pos.y += bullet1[i].vel.y * dt;
			if(bullet1[i].pos.y > WINDOW_HEIGHT){
				bullet1[i].active = false;
			}
		}
	}
	
	for(int i = 0; i< MAX_BULLETS; i++){
		if(IsKeyPressed(KEY_SPACE)){
			if(!bullet2[i].active){
				bullet2[i].active = true;
				bullet2[i].pos = p2->pos;
				bullet2[i].vel = (Vector2){0.0f,1500.0f};
				break;
			}

		}
		if(bullet2[i].active){
			bullet2[i].pos.y += bullet2[i].vel.y * dt;
			if(bullet2[i].pos.y > WINDOW_HEIGHT){
				bullet2[i].active = false;
			}
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
		.vel = {500.0f,500.0f},
		 GREEN
	};
	Player p2 =
	{
		.radius = P2_RADIUS,
		.pos = {RIGHT_SIDE_WINDOW_CENTER_X, WINDOW_HEIGHT/2.0f},
		.vel = {500.0f, 500.0f},
		RED
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
		{60.0f, 60.0f},
		RED	
	};
	
	Button b2 = {
		50.0f ,
		{1220.0f, 660.0f},
		GREEN
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

	Bullets p1_bullets[MAX_BULLETS];
	for(int i = 0; i < MAX_BULLETS; i++){
		p1_bullets[i].pos = (Vector2){0,0};
		p1_bullets[i].vel = (Vector2){1000.0f, 1000.0f};
		p1_bullets[i].radius = 5;
		p1_bullets[i].color = GREEN;
		p1_bullets[i].active = false;
	}
	
	Bullets p2_bullets[MAX_BULLETS];
	for(int i = 0; i < MAX_BULLETS; i++){
		p2_bullets[i].pos = (Vector2){0,0};
		p2_bullets[i].vel = (Vector2){1000.0f, 1000.0f};
		p2_bullets[i].radius = 5;
		p2_bullets[i].color = RED;
		p2_bullets[i].active = false;
	}
	
  GameState Game = PLAYING_STATE;
		
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);
	
	switch(Game)
	{
		case PLAYING_STATE:
			update_player(&p1, &p2, &boundary);
			level_one(&b1,&b2,&p1,&p2,&pressure_plate_leftside,&pressure_plate_rightside, p1_bullets, p2_bullets,&Game);

			DrawCircleV(b1.pos, b1.radius,b1.color);
			DrawCircleV(b2.pos, b2.radius,b2.color);
		
			DrawCircleV(p1.pos, p1.radius,p1.color);
			DrawCircleV(p2.pos, p2.radius,p2.color);

			for(int i = 0; i < MAX_BULLETS; i++){
				if(p1_bullets[i].active){
					DrawCircleV(p1_bullets[i].pos, p1_bullets[i].radius, p1_bullets[i].color);
				}
				if(p2_bullets[i].active){
					DrawCircleV(p2_bullets[i].pos, p2_bullets[i].radius, p2_bullets[i].color);
				}
			}
			DrawRectangleRec(pressure_plate_rightside,RED);
			DrawRectangleRec(pressure_plate_leftside,GREEN);
			
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

