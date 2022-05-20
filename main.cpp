#include "raylib.h"
#include <cstdlib>
#include <math.h>
#include <iostream>
#define DARKAQUA	(Color){3, 135, 91, 255}

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    int posx = screenWidth/2 - 25; int posy = screenHeight/2 + 100;
    int pos[6] = {0, 0, 10, 0, 20, 0};
    bool poss[6] = {true, true, true, true, true, true};
    int atirar[3] = {false, false, false};
    int ipos[6] = {0, 0, 0, 0, 0, 0};
    const char texto[7] = "Wave 1";
    int tempo = 0;
    bool wave = true;
    bool pdat = true;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    Font alagard = LoadFont("fonts/alagard.ttf"); 
    Texture2D space = LoadTexture("media/space.png");

    ipos[0] = rand() % -100;
    ipos[1] = rand() % 800;

    SetTargetFPS(60);           // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
	
	//Fazer o texto "Wave 1" desaparecer após 5 segundos
	//300 = frames, 5 = segundos. 60 frames = 1, 300 frames = 5 segundos. Se "tempo" = 300/5 se passou 1 segundo
	tempo++;
	if(300/5 == tempo){
		wave = false;
	}
	
	//Movementação
	if(IsKeyDown(KEY_A)){
		posx-=6;
	}
	if(IsKeyDown(KEY_D)){
		posx+=6;
	}
	if(IsKeyDown(KEY_W)){
		posy-=6;
	}
	if(IsKeyDown(KEY_S)){
		posy+=6;
	}

	//Ataque
	if(IsKeyPressed(KEY_SPACE)){
		if(poss[0] && poss[1]){
			pos[0] = posx + 25;
			pos[1] = posy;
			atirar[0] = true;
			poss[0] = false;
			poss[1] = false;
		}
		else if(poss[2] && poss[3]){
			pos[2] = posx + 25;
			pos[3] = posy;
			atirar[1] = true;
			poss[2] = false;
			poss[3] = false;
		}
		else if(poss[4] && poss[5]){
			pos[4] = posx + 25;
			pos[5] = posy;
			atirar[2] = true;
			poss[4] = false;
			poss[5] = false;
			pdat = false;
		}
	}
	if(atirar[0] == true){
		pos[1]-=5;
		if(pos[1] <= 0){
			atirar[0] = false;
		}
	}
	if(atirar[1] == true){
		pos[3]-=5;
		if(pos[3] <= 0){
			atirar[1] = false;
		}
	}
	if(atirar[2] == true){
		pos[5]-=5;
		if(pos[5] <= 0){
			atirar[2] = false;
		}
	}

	if(IsKeyPressed(KEY_R)){
		poss[0] = true;
		poss[1] = true;
		poss[2] = true;
		poss[3] = true;
		poss[4] = true;
		poss[5] = true;
		pdat = true;
	}

	//Inimigos
	ipos[1]+=5;
	if(ipos[1] >= 450){
		ipos[0] = rand() % 800;
		ipos[1] = rand() % 100 * -1;
	}
	//Colisão dos tiros com o inimigo
	if(pos[0] > ipos[0] && pos[0] < ipos[0] + 50 && pos[1] > ipos[1] && pos[1] < ipos[1] + 50){
		ipos[0] = rand() % 800;
		ipos[1] = rand() % 100 * -1;
		atirar[0] = false;
		pos[0] = 0;
		pos[1] = 0;
	}
	if(pos[2] > ipos[0] && pos[2] < ipos[0] + 50 && pos[3] > ipos[1] && pos[3] < ipos[1] + 50){
		ipos[0] = rand() % 800;
		ipos[1] = rand() % 100 * -1;
		atirar[1] = false;
		pos[2] = 10;
		pos[3] = 0;
	}
	if(pos[4] > ipos[0] && pos[4] < ipos[0] + 50 && pos[5] > ipos[1] && pos[5] < ipos[1] + 50){
		ipos[0] = rand() % 800;
		ipos[1] = rand() % 100 * -1;
		atirar[2] = false;
		pos[4] = 20;
		pos[5] = 0;
	}

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(BLACK);

	    DrawTexture(space, 0, 0, RED);
            DrawRectangle(posx, posy, 50, 50, GOLD);
	    DrawRectangle(pos[0], pos[1], 5, 5, GOLD);
	    DrawRectangle(pos[2], pos[3], 5, 5, GOLD);
	    DrawRectangle(pos[4], pos[5], 5, 5, GOLD);
	    DrawRectangle(ipos[0], ipos[1], 50, 50, DARKAQUA);
	    if(wave == true){
		DrawTextEx(alagard, texto, (Vector2){ screenWidth/2 - 50, screenHeight/2 - 50 }, 30, 1, RAYWHITE);
	    }
	    if(pdat == false){
		DrawTextEx(alagard, "Aperte R para recarregar", (Vector2){ 0, 422 }, 20, 1, RAYWHITE);
	    }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
