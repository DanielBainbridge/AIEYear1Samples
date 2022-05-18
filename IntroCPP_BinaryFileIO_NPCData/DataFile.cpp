#include "DataFile.h"
#include <fstream>
using namespace std;

DataFile::DataFile()
{
	recordCount = 0;
}
//when a datafile is destroyed it will run the clear function to regain memory
DataFile::~DataFile()
{
	Clear();
}

void DataFile::AddRecord(string imageFilename, string name, int age)
{
	Image i = LoadImage(imageFilename.c_str());

	Record* r = new Record;
	r->image = i;
	r->name = name;
	r->age = age;

	records.push_back(r);
	recordCount++;
}

DataFile::Record* DataFile::GetRecord(int offset, string filename)
{
		
	//find total space that one record takes up,
	//get index of the record
	ifstream infile(filename, ios::binary);
	int nameSize = 0;
	int ageSize = 0;
	int width = 0, height = 0, imageSize = 0;
	//offset gotten from record position vector
	offset = recordposition[offset];

	infile.seekg(offset, std::ios::beg);

	infile.read((char*)&width, sizeof(int));
	infile.read((char*)&height, sizeof(int));

	imageSize = sizeof(Color) * width * height;

	infile.read((char*)&nameSize, sizeof(int));
	infile.read((char*)&ageSize, sizeof(int));

	char* imgdata = new char[imageSize];
	infile.read(imgdata, imageSize);

	Image img = LoadImageEx((Color*)imgdata, width, height);
	//initialise character array as \0 values with one extra value to add the null value to cut the string off
	char* name = new char[nameSize + 1]{};
	int age = 0;

	infile.read((char*)name, nameSize);
	infile.read((char*)&age, ageSize);

	Record* r = new Record();
	r->image = img;
	r->name = string(name);
	r->age = age;
	delete[] imgdata;
	delete[] name;
	infile.close();
	return r;
}

void DataFile::Save(string filename)
{
	ofstream outfile(filename, ios::binary);

	int recordCount = records.size();
	outfile.write((char*)&recordCount, sizeof(int));

	for (int i = 0; i < recordCount; i++)
	{
		Color* imgdata = GetImageData(records[i]->image);

		int imageSize = sizeof(Color) * records[i]->image.width * records[i]->image.height;
		int nameSize = records[i]->name.length();
		int ageSize = sizeof(int);

		outfile.write((char*)&records[i]->image.width, sizeof(int));
		outfile.write((char*)&records[i]->image.height, sizeof(int));

		outfile.write((char*)&nameSize, sizeof(int));
		outfile.write((char*)&ageSize, sizeof(int));

		outfile.write((char*)imgdata, imageSize);
		outfile.write((char*)records[i]->name.c_str(), nameSize);
		outfile.write((char*)&records[i]->age, ageSize);
	}

	outfile.close();
}

void DataFile::Load(string filename)
{
	Clear();
	ifstream infile(filename, ios::binary);	
	recordCount = 0;
	infile.read((char*)&recordCount, sizeof(int));

	//basic idea create loadrecord function, use load to load total amount of records, if record is in range of total records then load that specific record.
	for (int i = 0; i < recordCount; i++) {

		int recordstart = 0;
		recordstart = infile.tellg();
		int nameSize = 0;
		int ageSize = 0;
		int width = 0, height = 0, imageSize = 0;		
		
		recordposition.push_back(recordstart);
		infile.read((char*)&width, sizeof(int));
		infile.read((char*)&height, sizeof(int));

		imageSize = sizeof(Color) * width * height;

		infile.read((char*)&nameSize, sizeof(int));
		infile.read((char*)&ageSize, sizeof(int));

		char* imgdata = new char[imageSize];

		infile.read(imgdata, imageSize);

		//initialise character array as \0 values with one extra value to add the null value to cut the string off
		char* name = new char[nameSize + 1]{};
		int age = 0;

		infile.read((char*)name, nameSize);
		infile.read((char*)&age, ageSize);		

		delete[] imgdata;
		delete[] name;
	}
	infile.close();
}
//deletes each record to regain memory space, then clears the vector records and sets the record count to 0
void DataFile::Clear()
{
	for (int i = 0; i < records.size(); i++)
	{
		delete records[i];
	}
	records.clear();
	recordCount = 0;
}