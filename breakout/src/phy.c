#include "phy.h"
#include <raylib.h>

int circle_x = WINDOW_W/2.0f;
int circle_y = WINDOW_H/2.0f;

void drawing_stuff(){
	
	BeginDrawing();
	
	ClearBackground(BLACK);

	DrawCircle(circle_x,circle_y, 5, RED);
	
	EndDrawing();
}
void Update_movement(){
	if(IsKeyDown(KEY_A)){
		circle_x -= 5.0f;	
	}
	if(IsKeyDown(KEY_D)){
		circle_x += 5.0f;	
	}

}

