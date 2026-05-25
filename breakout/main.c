#include "base.h"
#include <raylib.h>

#define	WINDOW_WIDTH		800
#define	WINDOW_HEIGHT		600

f32 ball_radius =	10.0f;

typedef struct{
	f32 width;
	f32 height;
	f32 xpos;
	f32 ypos;
}Paddle;


void update_ball(f32 *ball_x, f32 *ball_y, f32 *ball_xvel, f32 *ball_yvel){
	f32 dt = GetFrameTime();

	*ball_y += *ball_yvel * dt;
	*ball_x += *ball_xvel * dt;
	
	if(*ball_x > WINDOW_WIDTH-ball_radius || *ball_x < ball_radius){
			*ball_xvel *= -1.0f;
	}
	
	if(*ball_y > WINDOW_HEIGHT-ball_radius || *ball_y < ball_radius){
			*ball_yvel *= -1.0f;
	}
	if(ball_radius > 10.0f){
		ball_radius -= 30.0f*dt;
	}
}

void update_paddle(){

}


int main(){
	
	InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"breakout!");	
	
	f32 ball_x =			(WINDOW_WIDTH/2.0f);
	f32 ball_y =			(WINDOW_HEIGHT/2.0f);
	f32 ball_yvel =		500.0f;
	f32 ball_xvel =		500.0f;

	Paddle pd = {	
		.width = 50.0f,
		.height = 10.0f,
		.xpos = WINDOW_WIDTH/2.0f-pd.width,
		.ypos= WINDOW_HEIGHT-pd.height+2
	};
	
	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);

		update_ball(&ball_x, &ball_y, &ball_xvel, &ball_yvel);
		
		DrawCircle(ball_x, ball_y, ball_radius , RED);
		//DrawRectangle()

		EndDrawing();
		
	}

	CloseWindow();
	return 0;
}
