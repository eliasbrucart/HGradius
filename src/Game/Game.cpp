#include "Game.h"

#include "raylib.h"

#include "Global.h"
#include "Menu.h"
#include "GamePlay.h"
#include "FinalMenu.h"
#include "Credits.h"

namespace Game
{
	GameState state = GameState::GameMenu;

	void Loop()
	{
		InitWindowGame();
		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(BLACK);
			if (state == GameState::GameMenu)
			{
				Menu();
			}
			if (state == GameState::Game)
			{
				Update();
				Draw();
				timer++;
			}
			if (state == GameState::MenuFinal)
			{
				FinalMenu();
			}
			if (state == GameState::Credits)
			{
				CreditsScreen();
			}
			if (state == GameState::Close)
			{
				CloseWindow();
			}
			EndDrawing();
		}

	}
}

