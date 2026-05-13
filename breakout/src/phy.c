#include "phy.h"
#include <raylib.h>

void drawing_stuff(){
	
	BeginDrawing();
	
	ClearBackground(BLACK);

	DrawCircle(WINDOW_W/2,WINDOW_H/2, 50, RED);
	
	EndDrawing();
}

