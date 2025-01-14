#pragma once
#include <vector>
#include "raylib.h"
#include "WinInc.h"

struct Entity {
	float x = 0, y = 0;
	float rotation = 0;
	float speed = 0;
	unsigned char r = 0, g = 0, b = 0;
	float size = 1;
};

class EntityDisplayApp {
public:
	EntityDisplayApp(int screenWidth = 800, int screenHeight = 450);
	~EntityDisplayApp();

	bool Startup();
	void Shutdown();

	void Update(float deltaTime);
	void Draw();
	int* sizetempptr;

protected:
	int m_screenWidth;
	int m_screenHeight;
	HANDLE h = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, L"SharedEntities");
	int ENT_COUNT;
	Entity* m_entities;
};