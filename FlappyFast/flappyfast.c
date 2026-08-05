#include <raylib.h>
#include <stdio.h>
#include <stdbool.h>

#define WINDOWWIDTH		800
#define WINDOWMIDDLEX	400
#define WINDOWHEIGHT	600
#define WINDOWMIDDLEY	300
#define MAXPIPES		12
#define GAPSIZE			250

typedef enum {
	PLAYING,
	GAMEOVER,
	MENU
}GameState;

typedef struct {
	Vector2 pos;
	float Vel;
	float acc;
	int radius;
	bool IsMoving;
}Player;

typedef struct {
	Player flappy;
	Rectangle pipes[];
}Game;

void update_flappy(Player *flappy)
{
	float dt = GetFrameTime();
	
	flappy->Vel += flappy->acc * dt;
	flappy->pos.y += flappy->Vel * dt;

	if ((flappy->Vel > 800.0f))
	{
		flappy->Vel = 800.0f;
	}

	if(IsKeyPressed(KEY_SPACE))
	{
		flappy->Vel = -12000.0f * dt;
	}
}

void update_pipes(Rectangle *pipes, float *PipesXDisplacement, bool *amLazyForgiveMe ) {

	float dt = GetFrameTime();
	
	for (int i = 0; i < MAXPIPES; i+=2) {

		pipes[i].x -= 240.f * dt;
		pipes[i + 1].x -= 240.0f * dt;

		if (pipes[i].x < (-pipes->width * 2)) {

			amLazyForgiveMe[i] = true;
			pipes[i].x = 800;
			pipes[i + 1].x = 800;

			float randGap = GetRandomValue(-90, 50);
			float gapOffset = GetRandomValue(-20, 50);

			pipes[i].height = 240 + randGap;
			pipes[i + 1].y = pipes[i].height + (170 + gapOffset);
		}
		
	}
}
bool collision(Rectangle* pipe, Player* flappy) {
	bool collision =  false;
	for (int i = 0; i < MAXPIPES; i++) {
		if (CheckCollisionCircleRec(flappy->pos, flappy->radius, pipe[i])) return true;
	}
	return false;
}
void reseGame(Rectangle* pipes, Player* flappy, bool *IsRunning) {
	IsRunning = false;

	flappy->pos = (Vector2){ WINDOWMIDDLEX, WINDOWMIDDLEY };
	flappy->Vel = 150.0f;
	flappy->acc = 500.0f;
	flappy->radius = 10;

	float x = 800;

	for (int i = 0; i < MAXPIPES; i += 2)
	{
		pipes[i] = (Rectangle){ x, 0, 80, 240 };
		pipes[i + 1] = (Rectangle){ x, 360, 80, 500 };

		x += 160;
	}
}


int main()
{
	InitWindow(WINDOWWIDTH, WINDOWHEIGHT, "sighh!");

	Game game = {
		{ { WINDOWMIDDLEX, WINDOWMIDDLEY }, 150.0f, 500.0f, 10, false }
	};

	bool amLazyForgiveMe[MAXPIPES];
	for(int i = 0; i < MAXPIPES; i++){
		amLazyForgiveMe[i] = false;
	}

	float PipesXDisplacement = 0;
	
	Rectangle pipes[MAXPIPES] = {
		{ PipesXDisplacement, 0, 80, 240 },
		{ PipesXDisplacement, 360, 80, 500 },
		{ PipesXDisplacement+ 160, 0, 80, 240 },
		{ PipesXDisplacement+ 160, 360, 80, 500 },
		{ PipesXDisplacement+ 320, 0, 80, 240 },
		{ PipesXDisplacement+ 320, 360, 80, 500 },
		{ PipesXDisplacement+ 480, 0, 80, 240 },
		{ PipesXDisplacement+ 480, 360, 80, 500 },
		{ PipesXDisplacement+ 640, 0, 80, 240 },
		{ PipesXDisplacement+ 640, 360, 80, 500 },
		{ PipesXDisplacement+ 800, 0, 80, 240 },
		{ PipesXDisplacement+ 800, 360, 80, 500 }
	};

	SetTargetFPS(60);

	GameState state = MENU;
	int textsize1 = 0;
	int textsize2 = 0;
	
	while(!WindowShouldClose())
	{
		BeginDrawing();
		ClearBackground(BLACK);

		switch (state) {

		case MENU:
			textsize1 = MeasureText("Hello,\nTap Space to start the game!\nOr Esc to quit.", 30);
			DrawText("Hello,\nTap Space to start the game!\nOr Esc to quit.", WINDOWMIDDLEX - textsize1/2, WINDOWMIDDLEY - 45, 30, WHITE);

			if (IsKeyPressed(KEY_SPACE)) state = PLAYING;
			break;
		case PLAYING:
			if (IsKeyPressed(KEY_SPACE)) { game.flappy.IsMoving = true; }
			if (game.flappy.IsMoving) {
				update_flappy(&game.flappy);
				update_pipes(pipes, &PipesXDisplacement, amLazyForgiveMe);
			}
			
			for (int i = 0; i < MAXPIPES; i++) {
				if(amLazyForgiveMe[i]){
					DrawRectangleRec(pipes[i], WHITE);
				}
				if (collision(pipes, &game.flappy)) {
					state = GAMEOVER;
				}
			}
			DrawCircleV(game.flappy.pos,game.flappy.radius, BLUE);
			break;

		case GAMEOVER:
			reseGame(pipes, &game.flappy, &game.flappy.IsMoving);
			textsize2 = MeasureText("GAMEOVER", 30);
			DrawText("GAMEOVER", WINDOWMIDDLEX - textsize2/2, WINDOWMIDDLEY - 15, 30, WHITE);

			if (IsKeyPressed(KEY_R)) state = PLAYING;
			if (IsKeyPressed(KEY_TAB)) state = MENU;
			break;
		}
		EndDrawing();
	}
	
	CloseWindow();

	return 0;
}


