#include "Critter.h"
#include "HashTable.h"
Critter::Critter()
{
	m_position = Vector2{ 0, 0 };
	m_velocity = Vector2{ 0, 0 };
	m_radius = 0;
}

Critter::~Critter()
{
}

void Critter::Init(Vector2 position, Vector2 velocity, float radius, Texture2D texture)
{
	m_position = position;
	m_velocity = velocity;
	m_radius = radius;

	m_texture = texture;

	m_isLoaded = true;
}

void Critter::Update(float dt)
{

	m_position.x += m_velocity.x * dt;
	m_position.y += m_velocity.y * dt;

	m_isDirty = false;
	if (GetX() < 0) {
		SetX(0);
		SetVelocity(Vector2{ -GetVelocity().x,GetVelocity().y });
	}
	if (GetX() > GetScreenWidth()) {
		SetX(GetScreenWidth());
		SetVelocity(Vector2{ -GetVelocity().x, GetVelocity().y });
	}
	if (GetY() < 0) {
		SetY(0);
		SetVelocity(Vector2{ GetVelocity().x, -GetVelocity().y });
	}
	if (GetY() > GetScreenHeight()) {
		SetY(GetScreenHeight());
		SetVelocity(Vector2{ GetVelocity().x, -GetVelocity().y });
	}
}


void Critter::Draw()
{
	DrawTexture(m_texture, m_position.x - m_texture.width / 2.0f, m_position.y - m_texture.height / 2.0f, WHITE);
}
