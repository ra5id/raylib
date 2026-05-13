#include "base.h"
#include "phy.h"
#include <raylib.h>

void drawing_stuff(Vec2 *Cpos){

	BeginDrawing();

	ClearBackground(BLACK);
	DrawCircle(Cpos->x,Cpos->y, 5, RED);

	EndDrawing();
}
void Update_movement(Vec2 *Cpos, Vec2 *Cvel){
	
	f64 dt = GetFrameTime();

	if(Cpos->x > (WINDOW_W-5)){
		 Cvel->x *= -1;
	}
	if(Cpos->x < (0)){
		 Cvel->x *= -1;
	}
	if(Cpos->y > (WINDOW_H-5)){
		 Cvel->y *= -1;
	}
	if(Cpos->y < 0){
		 Cvel->y *= -1;
	}

	Cpos->x += Cvel->x * dt;
	Cpos->y += Cvel->y *dt;
}

