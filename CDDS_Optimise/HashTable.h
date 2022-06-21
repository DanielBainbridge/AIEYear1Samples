#pragma once
#include <functional>
#include <vector>
#include <utility>
#include "raylib.h"

class HashTable {
public:
	struct Entry {
		bool occupied;
		const char* name;
		Texture2D texture;
	};
	HashTable() {
		m_data.reserve(10);
		for (int i = 0; i < m_data.capacity(); i++)
		{
			m_data.emplace_back();
		}
	}

	~HashTable();

	Texture2D& operator[] (const char* key) {
		auto hashedKey = DJBHash(key, strlen(key)) % m_data.size();
		return m_data[hashedKey].texture;
	}

	void AddValue(const char* string);
	void RemoveValue(const char* string);
	void Clear();

private:
	std::vector <Entry> m_data;
	int numoccupied = 0;
	void CheckResize();
	unsigned int DJBHash(const char* string, unsigned int length);
};