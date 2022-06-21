#include "HashTable.h"

HashTable::~HashTable()
{
	for (int i = 0; i < m_data.size(); i++)
	{
		if (m_data[i].occupied)
		{
			UnloadTexture(m_data[i].texture);
		}
	}
}

void HashTable::AddValue(const char* string) {
	CheckResize();
	auto hashedkey = DJBHash(string, strlen(string)) % m_data.size();
	if (!m_data[hashedkey].occupied)
	{
		m_data[hashedkey] = {true, string, LoadTexture(string)};
		numoccupied++;
	}
	else
	{
		for (int i = hashedkey++; i < m_data.size(); i++) {
			if (!m_data[hashedkey].occupied)
			{
				m_data[hashedkey] = { true, string, LoadTexture(string) };
				numoccupied++;
				break;
			}
		}
	}

}

void HashTable::RemoveValue(const char* string) {
	auto hashedkey = DJBHash(string, strlen(string)) % m_data.size();
	for (unsigned int i = 0; i < m_data.size(); i++)
	{
		if (i == hashedkey)
		{
			m_data[i].occupied = false;
		}
	}
}

void HashTable::Clear() {
	m_data.clear();
}

void HashTable::CheckResize() {
	if (numoccupied >= m_data.size() / 1.25)
	{
		std::vector<Entry> newdata;
		newdata.reserve(m_data.size() * 2);
		for (int i = 0; i < newdata.capacity(); i++) {
			newdata.emplace_back();
		}
		for (int i = 0; i < m_data.size(); i++) {
			if (m_data[i].occupied)
			{
				auto hashedkey = DJBHash(m_data[i].name, strlen(m_data[i].name)) % newdata.size();
				newdata[hashedkey] = m_data[i];
			}
		}
		m_data = std::move(newdata);
	}
}

unsigned int HashTable::DJBHash(const char* string, unsigned int length)
{
	unsigned int hash = 5381;
	for (unsigned int i = 0; i < length; string++, i++)
	{
		hash = ((hash << 5) + hash) ^ (hash >> 27) ^ (*string);
	}
	return hash;
}
