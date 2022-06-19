#include "EntityDisplayApp.h"
#include <iostream>
EntityDisplayApp::EntityDisplayApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {

}

EntityDisplayApp::~EntityDisplayApp() {

}

bool EntityDisplayApp::Startup() {

	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	//reads handle of assigned memory from another program 'h' to get the size of the array
	sizetempptr = (int*)MapViewOfFile(h, FILE_MAP_READ, 0, 0, sizeof(int));
	//assigns 
	ENT_COUNT = *sizetempptr;
	//unmaps
	UnmapViewOfFile(h);

	//reads handle of assigned memory from another program 'h' includes array in read this time
	int* startmemptr = (int*)MapViewOfFile(h, FILE_MAP_READ, 0, 0, sizeof(int) + (sizeof(Entity) * ENT_COUNT));
	startmemptr++;

	Entity* entptr = (Entity*)startmemptr;
	//initialise array of "Entity" after moving the pointer past the size of the array
	m_entities = entptr;

	return true;
}

void EntityDisplayApp::Shutdown() {

	UnmapViewOfFile(h);
	CloseWindow();        // Close window and OpenGL context
}

void EntityDisplayApp::Update(float deltaTime) {

}

void EntityDisplayApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// draw entities
	for (int i = 0; i < ENT_COUNT; i++) {
		DrawRectanglePro(
			Rectangle{ m_entities[i].x, m_entities[i].y, m_entities[i].size, m_entities[i].size }, // rectangle
			Vector2{ m_entities[i].size / 2, m_entities[i].size / 2 }, // origin
			m_entities[i].rotation,
			Color{ m_entities[i].r, m_entities[i].g, m_entities[i].b, 255 });
	}

	// output some text, uses the last used colour
	DrawText("Press ESC to quit", 630, 15, 12, LIGHTGRAY);

	EndDrawing();
}