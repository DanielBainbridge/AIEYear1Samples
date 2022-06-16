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

class EntityEditorApp {
public:
	EntityEditorApp(int screenWidth = 800, int screenHeight = 450);
	~EntityEditorApp();

	bool Startup();
	void Shutdown();

	void Update(float deltaTime);
	void Draw();

protected:
	int m_screenWidth;
	int m_screenHeight;

	// define a block of entities that should be shared
	HANDLE h = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(ENTITY_COUNT) + sizeof(m_entities), L"SharedEntities");
	//send over the size of entities and each entity
	enum { ENTITY_COUNT = 500 };
	Entity m_entities[ENTITY_COUNT];

};