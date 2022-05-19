#pragma once

#include "raylib.h"
#include <string>
#include <vector>

using namespace std;

class DataFile
{
public:
	struct Record {
		Image image;
		string name;
		int age;
	};

private:
	int recordCount;
	std::vector<Record*> records;	//this vector used to save not to load.
	std::vector<int> recordposition;
	std::streamsize sizeofrecord;



public:
	DataFile();
	~DataFile();

	void AddRecord(string imageFilename, string name, int age);
	Record* GetRecord(int index, string filename);

	int GetRecordCount() { return recordCount; };

	void Save(string filename);
	void Load(string filename);

private:
	void Clear();

};

