#ifndef PHY_H
#define PHY_H

#define WINDOW_W 800
#define WINDOW_H 600

#include "base.h"
#include "raylib.h"


typedef struct{
	f32 x;
	f32 y;
}Vec2;

typedef struct{
	Rectangle rect;
	f32 vel;
}Paddle;

void drawing_stuff(Vec2 *Cpos, Rectangle *rect); 
void Update_ball(Vec2 *Cpos, Vec2 *Cvel, Paddle *p);
void Update_paddle(Paddle *p);


#endif
