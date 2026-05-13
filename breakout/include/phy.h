#ifndef PHY_H
#define PHY_H

#define WINDOW_W 800
#define WINDOW_H 600


#include "base.h"

typedef struct{
	f32 x;
	f32 y;
}Vec2;

void drawing_stuff(Vec2 *Cpos); 
void Update_movement(Vec2 *Cpos, Vec2 *Cvel);


#endif
