#include "EntityEditorApp.h"
#include <random>
#include <time.h>
#include <iostream>

#define RAYGUI_IMPLEMENTATION
#define RAYGUI_SUPPORT_ICONS
#include "raygui.h"


EntityEditorApp::EntityEditorApp(int screenWidth, int screenHeight) : m_screenWidth(screenWidth), m_screenHeight(screenHeight) {

}

EntityEditorApp::~EntityEditorApp() {

}

bool EntityEditorApp::Startup() {

	InitWindow(m_screenWidth, m_screenHeight, "EntityDisplayApp");
	SetTargetFPS(60);

	h = CreateFileMapping(INVALID_HANDLE_VALUE,
		nullptr,
		PAGE_READWRITE,
		0, sizeof(int) + (sizeof(Entity) * ENTITY_COUNT), L"SharedEntities");

	m_count = (int*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(int) + (sizeof(Entity) * ENTITY_COUNT));

	*m_count = ENTITY_COUNT;
	m_entities = (Entity*)(m_count + 1);
	srand(time(nullptr));
	for (int i = 0; i < ENTITY_COUNT; i++) {
		m_entities[i].x = rand() % m_screenWidth;
		m_entities[i].y = rand() % m_screenHeight;
		m_entities[i].size = 10;
		m_entities[i].speed = rand() % 100;
		m_entities[i].rotation = rand() % 360;
		m_entities[i].r = rand() % 255;
		m_entities[i].g = rand() % 255;
		m_entities[i].b = rand() % 255;
	}
	/*
	Entity* entitiesptr = (Entity*)MapViewOfFile(h, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(m_entities));
	entitiesptr = m_entities;*/
	return true;
}

void EntityEditorApp::Shutdown() {

	UnmapViewOfFile(h);
	CloseWindow();        // Close window and OpenGL context
}

void EntityEditorApp::Update(float deltaTime) {


	// select an entity to edit
	static int selection = 0;
	static bool selectionEditMode = false;
	static bool xEditMode = false;
	static bool yEditMode = false;
	static bool rotationEditMode = false;
	static bool sizeEditMode = false;
	static bool speedEditMode = false;
	static Color colorPickerValue = WHITE;


	if (GuiSpinner(Rectangle{ 90, 25, 125, 25 }, "Entity", &selection, 0, ENTITY_COUNT - 1, selectionEditMode)) selectionEditMode = !selectionEditMode;

	int intX = (int)m_entities[selection].x;
	int intY = (int)m_entities[selection].y;
	int intRotation = (int)m_entities[selection].rotation;
	int intSize = (int)m_entities[selection].size;
	int intSpeed = (int)m_entities[selection].speed;


	// display editable stats within a GUI	
	GuiGroupBox(Rectangle{ 25, 70, 480, 220 }, "Entity Properties");

	if (GuiValueBox(Rectangle{ 90, 90, 125, 25 }, "x", &intX, 0, m_screenWidth, xEditMode)) xEditMode = !xEditMode;
	m_entities[selection].x = intX;

	if (GuiValueBox(Rectangle{ 90, 120, 125, 25 }, "y", &intY, 0, m_screenHeight, yEditMode)) yEditMode = !yEditMode;
	m_entities[selection].y = intY;

	m_entities[selection].rotation = GuiSlider(Rectangle{ 90, 150, 125, 25 }, "rotation", TextFormat("%2.2f", m_entities[selection].rotation), m_entities[selection].rotation, 0, 360);
	m_entities[selection].size = GuiSlider(Rectangle{ 90, 180, 125, 25 }, "size", TextFormat("%2.2f", m_entities[selection].size), m_entities[selection].size, 0, 100);
	m_entities[selection].speed = GuiSlider(Rectangle{ 90, 210, 125, 25 }, "speed", TextFormat("%2.2f", m_entities[selection].speed), m_entities[selection].speed, 0, 100);

	colorPickerValue = GuiColorPicker(Rectangle{ 260, 90, 156, 162 }, Color{ m_entities[selection].r, m_entities[selection].g, m_entities[selection].b });
	m_entities[selection].r = colorPickerValue.r;
	m_entities[selection].g = colorPickerValue.g;
	m_entities[selection].b = colorPickerValue.b;


	// move entities

	for (int i = 0; i < ENTITY_COUNT; i++) {
		if (selection == i)
			continue;

		float s = sinf(m_entities[i].rotation) * m_entities[i].speed;
		float c = cosf(m_entities[i].rotation) * m_entities[i].speed;
		m_entities[i].x -= s * deltaTime;
		m_entities[i].y += c * deltaTime;

		// wrap position around the screen
		m_entities[i].x = fmod(m_entities[i].x, m_screenWidth);
		if (m_entities[i].x < 0)
			m_entities[i].x += m_screenWidth;
		m_entities[i].y = fmod(m_entities[i].y, m_screenHeight);
		if (m_entities[i].y < 0)
			m_entities[i].y += m_screenHeight;
	}
}

void EntityEditorApp::Draw() {
	BeginDrawing();

	ClearBackground(RAYWHITE);

	// draw entities
	for (int i = 0; i < ENTITY_COUNT; i++) {
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