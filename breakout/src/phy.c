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

