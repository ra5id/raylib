#include "base.h"
#include <raylib.h>
#include <stdbool.h>

#define	WINDOW_WIDTH			800
#define	WINDOW_HEIGHT			600
#define PADDLE_ACC				600
#define P_ACC_LIMIT				500
#define BALL_PADDLE_PUSH	0.35f
#define BALL_MAX_SPEED		500.0f
#define BRICK_ROWS				7
#define BRICK_COLS				10


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

typedef struct{
	f32 x;
	f32 y;
	f32 width;
	f32 height;
	bool is_alive;
}Brick;


void update_ball(Vec2 *ball_pos, Vec2 *ball_vel, f32 *ball_radius, Paddle *pd){
	f32 dt = GetFrameTime();

	ball_pos->y += ball_vel->y * dt;
	ball_pos->x += ball_vel->x * dt;
	
	if(ball_pos->x > WINDOW_WIDTH-*ball_radius ||
		 ball_pos->x < *ball_radius)
	{
		 ball_vel->x *= -1.0f;
	}

	if(ball_vel->x > BALL_MAX_SPEED)
	{
     ball_vel->x = BALL_MAX_SPEED;
  }

	if(ball_vel->x < -BALL_MAX_SPEED)
	{
     ball_vel->x = -BALL_MAX_SPEED;
	}

	if(ball_pos->y < *ball_radius-0.3f)
	{
		 ball_vel->y *= -1.0f;
	}

	if(ball_vel->y >0 && (
		 ball_pos->y > pd->ypos-*ball_radius &&
		 ball_pos->x > pd->xpos &&
		 ball_pos->x < pd->xpos+pd->width))
	{
		 ball_vel->x += pd->vel * BALL_PADDLE_PUSH;
		 ball_vel->y *= -1.0f;
	}

}

void update_paddle(Paddle *pd){
	f32 dt = GetFrameTime();

	if(IsKeyDown(KEY_A)|| IsKeyDown(KEY_LEFT)){
		if(pd->vel > 0){
			 pd->vel = 0;
		}
		pd->vel -= PADDLE_ACC * dt;
	}

	if(IsKeyDown(KEY_D)|| IsKeyDown(KEY_RIGHT)){
		if(pd->vel < 0){
			 pd->vel = 0;
		}
		pd->vel += PADDLE_ACC * dt;
	}
	
	if((!IsKeyDown(KEY_A) && !IsKeyDown(KEY_LEFT)) &&
	   (!IsKeyDown(KEY_D) && !IsKeyDown(KEY_RIGHT)))
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

void update_bricks(Brick bricks[BRICK_ROWS][BRICK_COLS], Vec2 *ball_pos, Vec2 *ball_vel, f32 ball_radius, i32 *score, i32 *game_score){
	for(i32 row = 0; row < BRICK_ROWS; row ++){
		for(i32 col = 0; col < BRICK_COLS; col++){
			Brick *brick = &bricks[row][col];
			if(!brick->is_alive){
				continue;
			}

			bool collision_x = (ball_pos->x+ball_radius) > brick->x && 
												 (ball_pos->x+ball_radius) < (brick->x + brick->width);

			bool collision_y = (ball_pos->y+ball_radius) < (brick->y + brick->height) && 
												 (ball_pos->y+ball_radius) > brick->y;

			if(collision_x && collision_y){
				brick->is_alive = false;
				ball_vel->y *= -1.0f;
				*score += 1;
				*game_score += 1;


			}
		}
	}		
}

void reset_bricks(Brick bricks[BRICK_ROWS][BRICK_COLS])
  {
    for (i32 row = 0; row < BRICK_ROWS; row++) {
        for (i32 col = 0; col < BRICK_COLS; col++) {
            Brick *brick = &bricks[row][col];
              brick->x = 10.0f + col * 75.0f;
              brick->y = 10.0f + row * 25.0f;
              brick->width = 70.0f;
              brick->height = 20.0f;
              brick->is_alive = true;
          }
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
	i32 score = 0;
	i32 game_score = 0;
	
	Brick bricks[BRICK_ROWS][BRICK_COLS];

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
				game_score = 0;
				reset_bricks(bricks);
				ball_pos.x	=		WINDOW_WIDTH/2.0f;
				ball_pos.y	=		WINDOW_HEIGHT/2.0f;
				ball_vel.x	=		200.0f;
				ball_vel.y	=		250.0f;		
				pd.xpos = WINDOW_WIDTH/2.0f-paddle_width/2.0f;
				pd.ypos = WINDOW_HEIGHT-paddle_height;
				pd.vel = 0.0f;
				state = PLAYING_STATE;
			}
		}

		if(state == PLAYING_STATE){

			update_paddle(&pd);
			update_ball(&ball_pos, &ball_vel, &ball_radius, &pd);
			update_bricks(bricks, &ball_pos,&ball_vel,ball_radius,&score, &game_score);
			
			for(i32 row = 0; row < BRICK_ROWS; row++){
				for(i32 col = 0; col < BRICK_COLS; col++){
					Brick *brick = &bricks[row][col];
					if(brick->is_alive){
						DrawRectangle(
							brick->x,
							brick->y,
							brick->width,
							brick->height,
							BEIGE
						);
					}
				}
			}

			DrawCircle(ball_pos.x,ball_pos.y, ball_radius , RED);
			DrawRectangle(pd.xpos,pd.ypos,pd.width, pd.height, BEIGE);
			DrawText(TextFormat("TotalScore: %d",score), 5, WINDOW_HEIGHT-35, 15, BLUE);
			DrawText(TextFormat("Score: %d",game_score), 5, WINDOW_HEIGHT-15, 15, WHITE);

			
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
				game_score = 0;
				reset_bricks(bricks);
				ball_pos.x	=		WINDOW_WIDTH/2.0f;
				ball_pos.y	=		WINDOW_HEIGHT/2.0f;
				ball_vel.x	=		200.0f;
				ball_vel.y	=		250.0f;		
				pd.xpos = WINDOW_WIDTH/2.0f-paddle_width/2.0f;
				pd.ypos = WINDOW_HEIGHT-paddle_height;
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

