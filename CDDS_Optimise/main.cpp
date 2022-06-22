/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"
#include "raymath.h"
#include <random>
#include <time.h>
#include "Critter.h"
#include "HashTable.h"
#include "Link_List.h"
#include <cstring>
#include <string>
#include <iostream>

int main(int argc, char* argv[])
{
	// Initialization
	//--------------------------------------------------------------------------------------
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

	//SetTargetFPS(60);
	//--------------------------------------------------------------------------------------
	srand(time(NULL));

	//hash table in main
	//critter cpp load texture
	//critter cpp  needs to know hash table

	// create some critters
	const int CRITTER_COUNT = 20;
	const int MAX_VELOCITY = 80;
	HashTable hTable;
	hTable.AddValue("res/10.png");
	hTable.AddValue("res/9.png");
	LinkedList<Critter*> enemyAlive = LinkedList<Critter*>();
	LinkedList<Critter*> enemyDead = LinkedList<Critter*>();

	LinkedList<int> intlist = LinkedList<int>();

	for (auto i : intlist) {
		std::cout << i << std::endl;
	}


	for (int i = 0; i < CRITTER_COUNT; i++)
	{
		// create a random direction vector for the velocity
		Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
		// normalize and scale by a random speed
		velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);

		// create a critter in a random location
		Critter* newCritter = new Critter();
		newCritter->Init({ (float)(5 + rand() % (screenWidth - 10)), (float)(5 + (rand() % screenHeight - 10)) }, velocity, 12, hTable["res/10.png"]);
		enemyAlive.pushBack(newCritter);
	}


	Critter destroyer;
	Vector2 velocity = { -100 + (rand() % 200), -100 + (rand() % 200) };
	velocity = Vector2Scale(Vector2Normalize(velocity), MAX_VELOCITY);
	destroyer.Init(Vector2{ (float)(screenWidth >> 1), (float)(screenHeight >> 1) }, velocity, 20, hTable["res/9.png"]);

	float timer = 1;
	Vector2 nextSpawnPos = destroyer.GetPosition();

	// Main game loop
	while (!WindowShouldClose())    // Detect window close button or ESC key
	{
		// Update
		//----------------------------------------------------------------------------------
		// TODO: Update your variables here
		//----------------------------------------------------------------------------------

		float delta = GetFrameTime();

		destroyer.Update(delta);
		for (auto i = enemyAlive.begin(); i != enemyAlive.end(); i++) {
			(*i)->Update(delta);
			float dist = Vector2Distance((*i)->GetPosition(), destroyer.GetPosition());
			if (dist < (*i)->GetRadius() + destroyer.GetRadius()) {
				enemyDead.pushBack((*i));
				std::cout << "added to dead list" << std::endl;
				i = enemyAlive.erase(enemyAlive.find((*i)));
				std::cout << "erased from alive" << std::endl;
				continue;
			}
			for (auto j = enemyAlive.begin(); j != enemyAlive.end(); j++)
			{			
				if (i == j || (*i)->IsDirty())continue;

				float dist = Vector2Distance((*i)->GetPosition(), (*j)->GetPosition());
				if (dist < (*i)->GetRadius() + (*j)->GetRadius())
				{
					// collision!
					// do math to get critters bouncing
					Vector2 normal = Vector2Normalize(Vector2Subtract((*j)->GetPosition(), (*i)->GetPosition()));

					// not even close to real physics, but fine for our needs
					(*i)->SetVelocity(Vector2Scale(normal, -MAX_VELOCITY));
					// set the critter to *dirty* so we know not to process any more collisions on it
					(*j)->SetDirty();

					// we still want to check for collisions in the case where 1 critter is dirty - so we need a check 
					// to make sure the other critter is clean before we do the collision response
					if (!(*j)->IsDirty()) {
						(*j)->SetVelocity(Vector2Scale(normal, MAX_VELOCITY));
						(*j)->SetDirty();
					}
					break;
				}
			}
		}
		for (auto i = enemyAlive.begin(); i != enemyAlive.end(); i++)
		{
		}



		timer -= delta;

		if (timer <= 0)
		{
			timer = 1;
			if (enemyDead.m_count > 0)
			{
				if (enemyDead.m_count > 10)
				{
					std::cout << "ahhh" << std::endl;
				}
				if (enemyDead.begin() != nullptr)
				{
					Critter* respawnCritter = *enemyDead.begin();
					Vector2 normal = Vector2Normalize(destroyer.GetVelocity());

					// get a position behind the destroyer, and far enough away that the critter won't bump into it again
					Vector2 pos = destroyer.GetPosition();
					pos = Vector2Add(pos, Vector2Scale(normal, -50));
					// its pretty ineficient to keep reloading textures. ...if only there was something else we could do
					respawnCritter->Init(pos, Vector2Scale(normal, -MAX_VELOCITY), 12, hTable["res/10.png"]);
					enemyDead.popFront();
					enemyAlive.pushBack(respawnCritter);
					std::cout << "alive again!" << std::endl;
				}
			}
			nextSpawnPos = destroyer.GetPosition();
		}

		// Draw
		//----------------------------------------------------------------------------------
		BeginDrawing();

		ClearBackground(RAYWHITE);

		// draw the critters       
		for (auto critter : enemyAlive)
		{
			critter->Draw();
		}

		// draw the destroyer
		// (if you're wondering why it looks a little odd when sometimes critters are destroyed when they're not quite touching the 
		// destroyer, it's because the origin is at the top-left. ...you could fix that!)
		destroyer.Draw();

		DrawFPS(10, 10);
		std::string alivecount = std::to_string(enemyAlive.m_count);
		DrawText(alivecount.c_str(), 10, 50, 25, RED);
		std::string deadcount = std::to_string(enemyDead.m_count);
		DrawText(deadcount.c_str(), 10, 100, 25, RED);
		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
		//----------------------------------------------------------------------------------
	}

	// De-Initialization
	//--------------------------------------------------------------------------------------   
	CloseWindow();        // Close window and OpenGL context
	//--------------------------------------------------------------------------------------

	return 0;
}