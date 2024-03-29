#include "GamePlay.h"

#include "Global.h"
#include "Player.h"
#include "Enemy.h"
#include "Asteroid.h"
#include "Bullet.h"
#include "Game.h"

namespace Game
{
	static bool pause = false;

	static int heightDivisor = 7;

	static int fontSizePause = 50;

	static float tenSeconds = 10.0f;

	void DrawGamePlay()
	{
		ClearBackground(BLACK);
	}

	void InitGame()
	{
		DrawGamePlay();
		InitPlayer();
		InitEnemy();
		DrawEnemy();
		InitAsteroid();
		InitBullet();
		lifesPlayer = 3;
		limitEnemies = false;
		timer = 0.0f;
	}

	void DrawEnemys()
	{
		for (int i = 0; i < enemiesSize; i++)
		{
			if (limitEnemies == false)
			{
				framesCounter += GetFrameTime();

				if (framesCounter >= (maxCounter))
				{
					framesCounter = 0;

					currentFrame++;
					if (currentFrame > 1)
						currentFrame = 0;

					frameRec.x = static_cast<float>(currentFrame*(enemies[i].sprite.width / 2));
				}
				enemyPosition = { enemies[i].rec.x -100.0f, enemies[i].rec.y - 10.0f};

				DrawTextureRec(enemies[i].sprite, frameRec, enemyPosition, WHITE);
				//DrawRectangle(static_cast<int>(enemies[i].rec.x), static_cast<int>(enemies[i].rec.y), static_cast<int>(enemies[i].rec.width), static_cast<int>(enemies[i].rec.height), GREEN);
				countEnemy++;
				if (countEnemy == enemiesSize)
				{
					limitEnemies = true;
				}
			}
		}
		countEnemy = 0;
		limitEnemies = false;
	}

	void MoveEnemys()
	{
		for (int i = 0; i < enemiesSize; i++)
		{
			if (enemies[i].isAlive == true)
			{
				enemies[i].rec.x -= speedEnemy * GetFrameTime();
			}
		}
	}

	void LimitScreenEnemy()
	{
		for (int i = 0; i < enemiesSize; i++)
		{
			if (enemies[i].rec.x <= minScreenWidth)
			{
				enemies[i].rec.x = screenWidth;
				enemies[i].rec.y = GetRandomValue(screenHeight, screenHeight / heightDivisor);
			}
		}

	}

	void DrawAsteroids()
	{
		if (timer / static_cast<float>(GetFPS()) > tenSeconds)
		{
			for (int i = 0; i < asteroidSize; i++)
			{
				DrawTexture(asteroid1[i].sprite, asteroid1[i].rec.x, asteroid1[i].rec.y, WHITE);
			}
		}
	}

	void MoveAsteroids()
	{
		for (int i = 0; i < asteroidSize; i++)
		{
			if (asteroid1[i].isAlive == true)
			{
				asteroid1[i].rec.x -= speedAsteroid * GetFrameTime();
			}
		}
	}

	void MoveBullets()
	{
		for (int i = 0; i < bulletSize; i++)
		{
			bullets[i].rec.x += 600.0f * GetFrameTime();
		}
	}

	void LimitScreenAsteroids()
	{
		for (int i = 0; i < asteroidSize; i++)
		{
			if (asteroid1[i].rec.x <= minScreenWidth)
			{
				asteroid1[i].rec.x = screenWidth;
				asteroid1[i].rec.y = GetRandomValue(screenHeight, screenHeight / heightDivisor);
			}
		}
	}

	void LimitScreenBullet()
	{
		for (int i = 0; i < bulletSize; i++)
		{
			if (bullets[i].rec.x >= screenWidth)
			{
				if (bullets[i].isAlive == true)
				{
					//bullets[i].isAlive = false;
					InitBullet();
				}
			}
		}
		
	}

	void CheckCollisionEnemyPlayer()
	{
		for (int i = 0; i < enemiesSize; i++)
		{
			if (CheckCollisionRecs(player1.rec, enemies[i].rec))
			{
				enemies[i].isAlive = false;
				lifesPlayer--;
			}
		}
		
	}

	void CheckCollisionBulletEnemy()
	{
		for (int i = 0; i < enemiesSize; i++)
		{
			if (CheckCollisionRecs(bullets[i].rec, enemies[i].rec))
			{
				enemies[i].rec.x = -500.0f;
				enemies[i].rec.y = -500.0f;
				bullets[i].isAlive = false;
			}
		}
		
	}

	void CheckLifesPlayer() 
	{
		if (lifesPlayer <= 0)
		{
			state = GameState::MenuFinal;
		}
	}

	void ShootInput()
	{
		if (IsKeyDown(KEY_SPACE))
		{
			for (int i = 0; i < bulletSize; i++)
			{
				bullets[i].isAlive = true;
			}
		}
	}

	void PauseInput()
	{
		if (IsKeyPressed(KEY_P))
		{
			pause = true;
		}
	}

	void BackMenuInput()
	{
		if (IsKeyDown(KEY_M))
		{
			state = GameState::GameMenu;
		}
	}

	void Update()
	{
		if (pause == false)
		{
			MovePlayer();
			LimitMove();
			MoveEnemys();
			LimitScreenEnemy();
			MoveAsteroids();
			for (int i = 0; i < bulletSize; i++)
			{
				if (bullets[i].isAlive == true)
				{
					MoveBullets();
				}
			}
			LimitScreenAsteroids();
			LimitScreenBullet();
			CheckCollisionEnemyPlayer();
			CheckCollisionBulletEnemy();
			CheckLifesPlayer();
			ShootInput();
			PauseInput();
			BackMenuInput();
		}
		else
		{
			DrawText("PAUSA", halfScreenWidth, halfScreenHeight, fontSizePause, WHITE);
			if (IsKeyPressed(KEY_P))
			{
				pause = false;
			}
		}
		
	}

	void Draw()
	{
		DrawPlayer();
		DrawAsteroids();
		DrawEnemys();
		for (int i = 0; i < bulletSize; i++)
		{
			if (bullets[i].isAlive == true)
			{
				DrawBullet();
			}
		}
	}
}