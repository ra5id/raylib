#include "base.h"
#include "phy.h"
#include <raylib.h>

#define BASE_ACC 2200.0f

void drawing_stuff(Vec2 *Cpos, Rectangle *rect){

	BeginDrawing();

	ClearBackground(BLACK);
	DrawCircle(Cpos->x,Cpos->y, 5, RED);
	DrawRectangleRec(*rect, WHITE);


	EndDrawing();
}
void Update_ball(Vec2 *Cpos, Vec2 *Cvel, Paddle *p){

	f32 dt = GetFrameTime();
	

	if(Cpos->x > (WINDOW_W-5)){
		 Cvel->x *= -1;
	}
	if(Cpos->x < (0)){
		 Cvel->x *= -1;
	}
	if(Cpos->y > (p->rect.y-8) && Cpos->x > p->rect.x && Cpos->x < p->rect.x+100){
		 Cvel->y *= -1;
	}
	if(Cpos->y < 0){
		 Cvel->y *= -1;
	}
	if(Cpos->y > WINDOW_H+5){
		 Cvel->x = 0;
		 Cvel->y = 0;
	}
		Cpos->x += Cvel->x * dt;
		Cpos->y += Cvel->y *dt;
}

void Update_paddle(Paddle *p){
		
	f32 dt = GetFrameTime();
	
	if(p->rect.x <0){
	   p->rect.x = 0;
	}
	if(p->rect.x > WINDOW_W-100){
	   p->rect.x = WINDOW_W-100;
	}
	
	p->vel *= 0.92f;
	

	if(IsKeyDown(KEY_D)){
		p->vel += BASE_ACC * dt;
	}

	if(IsKeyDown(KEY_A)){
    p->vel -= BASE_ACC * dt;
	}
	
	p->rect.x += p->vel * dt;
}

	void check_gameover(Vec2 *Cpos, Vec2 *Cvel){
;
	bool running = true;
	if(Cpos->y > WINDOW_H){
		running = false;
	}
	if(!running){	
		i32 GAMEOVER_S = MeasureText("GAMEOVER",40);
		i32 RESTART_S = MeasureText("press 'r' to restart", 20);
		DrawText("GAMEOVER", (WINDOW_W/2)-(GAMEOVER_S/2),WINDOW_H/2-20,40,RED);
		DrawText("press 'r' to restart", (WINDOW_W/2)-(RESTART_S/2),WINDOW_H/2+20,20,RED);
		if(IsKeyPressed(KEY_R)){
			running = true;
			ClearBackground(BLACK);
			Cpos->x = WINDOW_W/2.0f;
			Cpos->y = WINDOW_H/2.0f;
			Cvel->x = 300;
			Cvel->y = 300;
		}	
	}
}
