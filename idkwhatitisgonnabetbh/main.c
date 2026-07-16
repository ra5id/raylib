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
#define BULLET_SPEED 1500.0f

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

void level_one(Button *b1, Button *b2, Player *p1, Player *p2, Rectangle *pl, Rectangle *pr, Bullets *bullet1,Bullets *bullet2, bool *is_Task_completed, GameState *Game, i32 *count_p1, i32 *count_p2)
{
	f32 dt = GetFrameTime();
	
	for(int i = 0; i< MAX_BULLETS; i++){
		if(IsKeyPressed(KEY_SPACE)){
			if(!bullet1[i].active){
				bullet1[i].active = true;
				bullet1[i].pos = p1->pos;
				bullet1[i].vel = (Vector2){0.0f,BULLET_SPEED};
				break;
			}

		}
		if(bullet1[i].active){
			bullet1[i].pos.y += bullet1[i].vel.y * dt;
			if(CheckCollisionCircleRec(bullet1[i].pos,bullet1[i].radius, *pl)){
				*count_p1 += 1;
				printf("HIT!\n");
				bullet1[i].active = false;
			}
			if(bullet1[i].pos.y > WINDOW_HEIGHT){
				bullet1[i].active = false;
			}
		}
	}
	
	for(int i = 0; i< MAX_BULLETS; i++){
		if(IsKeyPressed(KEY_KP_0)){
			if(!bullet2[i].active){
				bullet2[i].active = true;
				bullet2[i].pos = p2->pos;
				bullet2[i].vel = (Vector2){0.0f,BULLET_SPEED};
				break;
			}

		}
		if(bullet2[i].active){
			bullet2[i].pos.y += bullet2[i].vel.y * dt;
			if(CheckCollisionCircleRec(bullet2[i].pos,bullet2[i].radius, *pr)){
				*count_p2 += 1;		
				printf("HIT!\n");
				bullet2[i].active = false;
			}
			if(bullet2[i].pos.y > WINDOW_HEIGHT){
				bullet2[i].active = false;
			}
		}
	}	
	
	if(*count_p1 > 50 && *count_p2 > 50){
		*is_Task_completed = true;
	}

		
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

	bool main_task_completed = false;
	 
	i8 count = 5;
	i16 textwidth[5] = 	{MeasureText("Start New Game!",80),MeasureText("Continue!",60),MeasureText("Level selection?",60),MeasureText("Load Game...",60),MeasureText("Quit Game?",60)};

	i16 textheight[5] = {80,60,60,60,60};

	const	char *startmenu_texts[5] = 
	{
		"Start New Game!",
		"Continue!",
		"Level selection?",
		"Load Game...",
		"Quit Game?"
	};
		
	i16 text_x[5] = {20,20,20,20,20};

	i16 text_y[5] = {
		WINDOW_HEIGHT-500,
		WINDOW_HEIGHT-400,
		WINDOW_HEIGHT-300,
		WINDOW_HEIGHT-200,
		WINDOW_HEIGHT-100,
	};
	
	Rectangle game_startmenu_text[5] =
	{
		{text_x[0],text_y[0],textwidth[0],textheight[0]},
		{text_x[1],text_y[1],textwidth[1],textheight[1]},
		{text_x[2],text_y[2],textwidth[2],textheight[2]},
		{text_x[3],text_y[3],textwidth[3],textheight[3]},
		{text_x[4],text_y[4],textwidth[4],textheight[4]}
	};

	i32 level1_task_count_p1 = 0;
	i32 level1_task_count_p2 = 0;

	
  GameState Game = START_MENU_STATE;
		
	while(!WindowShouldClose())
  {
		BeginDrawing();
		ClearBackground(BLACK);

		f32 dt = GetFrameTime();
	
	switch(Game)
	{

		case START_MENU_STATE:
			Vector2 mouse = GetMousePosition();
			for(int i = 0; i < count; i++){
				
				DrawText(startmenu_texts[i],text_x[i],text_y[i],textheight[i],WHITE);
				
				if(CheckCollisionPointRec(mouse,game_startmenu_text[i])){
					if(i == 0){
						textheight[i] = 120;
						game_startmenu_text[i].height = 120;
					}else{
						textheight[i] = 100;
						game_startmenu_text[i].height = 100;
					}
					if(i==0 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
						Game = PLAYING_STATE;
					}
				

				}else{
					if(i==0){
						textheight[i] = 80;
						game_startmenu_text[i].height = 80;
					}else{
						textheight[i] = 60;
						game_startmenu_text[i].height = 60;
					}
				}
			}

			break;

		case PLAYING_STATE:
			update_player(&p1, &p2, &boundary);
			level_one(&b1,&b2,&p1,&p2,&pressure_plate_leftside,&pressure_plate_rightside, p1_bullets, p2_bullets, &main_task_completed,&Game,&level1_task_count_p1, &level1_task_count_p2);
			

			if(main_task_completed){
				DrawCircleV(b1.pos, b1.radius,b1.color);
				DrawCircleV(b2.pos, b2.radius,b2.color);
			}
			
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

			DrawText(TextFormat("%d", level1_task_count_p1),40,0,20, WHITE);
			DrawText(TextFormat("%d", level1_task_count_p2),WINDOW_WIDTH-40,0,20, WHITE);

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

