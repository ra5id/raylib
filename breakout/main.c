#include "base.h"
#include <raylib.h>

#define	WINDOW_WIDTH		800
#define	WINDOW_HEIGHT		600
#define PADDLE_ACC			600
#define P_ACC_LIMIT			500

typedef struct{
	f32 x;
	f32 y;
}Vec2;

typedef struct{
	f32 width;
	f32 height;
	f32 xpos;
	f32 ypos;
	f32 vel;
}Paddle;

typedef enum{
	MENU_STATE,
	PLAYING_STATE,
	GAME_OVER_STATE
}GameState;


void update_ball(Vec2 *ball_pos, Vec2 *ball_vel, f32 *ball_radius, Paddle *pd){
	f32 dt = GetFrameTime();

	ball_pos->y += ball_vel->y * dt;
	ball_pos->x += ball_vel->x * dt;
	
	if(ball_pos->x > WINDOW_WIDTH-*ball_radius ||
		 ball_pos->x < *ball_radius)
	{
		 ball_vel->x *= -1.0f;
	}

	if(ball_pos->y < *ball_radius ||
	  (ball_vel->y >0 && (
		 ball_pos->y >= pd->ypos-*ball_radius &&
		 ball_pos->x > pd->xpos &&
		 ball_pos->x < pd->xpos+pd->width)))
	{
		 ball_vel->y *= -1.0f;
	}
}

void update_paddle(Paddle *pd){
	f32 dt = GetFrameTime();

	if(IsKeyDown(KEY_A)){
		if(pd->vel > 0){
			 pd->vel = 0;
		}
		pd->vel -= PADDLE_ACC * dt;
	}

	if(IsKeyDown(KEY_D)){
		if(pd->vel < 0){
			 pd->vel = 0;
		}
		pd->vel += PADDLE_ACC * dt;
	}
	
	if(!IsKeyDown(KEY_A) &&
		 !IsKeyDown(KEY_D))
	{
			pd->vel -= pd->vel *3.0f * dt;
	}

	if(pd->vel > P_ACC_LIMIT){
		 pd->vel = P_ACC_LIMIT;
	}

	if(pd->vel < -P_ACC_LIMIT){
		 pd->vel = -P_ACC_LIMIT;
	}
	
	pd->xpos += pd->vel * dt;

	if(pd->xpos < 0){
		 pd->xpos = 0;
	}

	if(pd->xpos > (WINDOW_WIDTH-pd->width)){
		 pd->xpos = WINDOW_WIDTH-pd->width;				
	}

}


int main(){
	
	InitWindow(WINDOW_WIDTH,WINDOW_HEIGHT,"breakout!");	
	
	Vec2 ball_pos	=	{WINDOW_WIDTH/2.0f,
									 WINDOW_HEIGHT/2.0f};
	Vec2 ball_vel	=	{200.0f,250.0f};
	f32 ball_radius =	5.0f;

	f32 paddle_width	= 90.0f;
	f32 paddle_height	= 7.0f;
	
	Paddle pd = {	
		.width = paddle_width,
		.height = paddle_height,
		.xpos = WINDOW_WIDTH/2.0f-paddle_width/2.0f,
		.ypos = WINDOW_HEIGHT-paddle_height,
		.vel = 0.0f
	};
	
	GameState state = MENU_STATE;

	while(!WindowShouldClose()){
		BeginDrawing();
		ClearBackground(BLACK);

		if(state == MENU_STATE){
			i16 text1_width = MeasureText("START GAME?", 60);
			i16 text2_width = MeasureText("PRESS SPACE TO START!", 20);
			i16 text3_width = MeasureText("ESC TO QUIT", 20);
			DrawText("START GAME?",(WINDOW_WIDTH/2)-text1_width/2, 200,60, BLUE);
			DrawText("PRESS SPACE TO START!",(WINDOW_WIDTH/2)-text2_width/2, 265,20, GREEN);
			DrawText("ESC TO QUIT",(WINDOW_WIDTH/2)-text3_width/2, 285,20, RED);
		
			if(IsKeyPressed(KEY_SPACE)){
				state = PLAYING_STATE;
			}
		}

		if(state == PLAYING_STATE){
			update_paddle(&pd);
			update_ball(&ball_pos, &ball_vel, &ball_radius, &pd);
			
			DrawCircle(ball_pos.x,ball_pos.y, ball_radius , RED);
			DrawRectangle(pd.xpos,pd.ypos,pd.width, pd.height, BEIGE);
			
			if(ball_pos.y > WINDOW_HEIGHT+ball_radius){
				state = GAME_OVER_STATE;
			}
		}

		if(state == GAME_OVER_STATE){
			i16 text1_width = MeasureText("GAME OVER!!", 60);
			i16 text2_width = MeasureText("PRESS 'R' TO RESTART!", 20);
			i16 text3_width = MeasureText("TAB TO RETURN TO MAIN MENU", 20);
			i16 text4_width = MeasureText("ESC TO QUIT", 20);
			DrawText("GAME OVER!!",(WINDOW_WIDTH/2)-text1_width/2, 200,60, BLUE);
			DrawText("PRESS 'R' TO RESTART!",(WINDOW_WIDTH/2)-text2_width/2, 265,20, GREEN);
			DrawText("TAB TO RETURN TO MAIN MENU",(WINDOW_WIDTH/2)-text3_width/2, 285,20, YELLOW);
			DrawText("ESC TO QUIT",(WINDOW_WIDTH/2)-text4_width/2, 305,20, RED);
				
			if(IsKeyPressed(KEY_R)){
				ball_pos.x	=		WINDOW_WIDTH/2.0f;
				ball_pos.y	=		WINDOW_HEIGHT/2.0f;
				ball_vel.x	=		200.0f;
				ball_vel.y	=		250.0f;		
				pd.xpos = WINDOW_WIDTH/2.0f-paddle_width/2.0f,
				pd.ypos = WINDOW_HEIGHT-paddle_height,
				pd.vel = 0.0f;
				state = PLAYING_STATE;
			}
			if(IsKeyPressed(KEY_TAB)){
				state = MENU_STATE;
			}
		}	
		
		EndDrawing();
		
	}

	CloseWindow();
	return 0;
}
