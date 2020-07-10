#pragma once
#include <fstream>

class LABEL_FILE
{
private:
	int _magicNumber;
	int _items;
	unsigned char* _data;

	const char* _filePath;
public:
	LABEL_FILE(const char* filePath)
		:_filePath(filePath)
	{
		std::ifstream file(filePath, std::ios::binary);
		
		char temp[5];

		file.get(temp[3]);
		file.get(temp[2]);
		file.get(temp[1]);
		file.get(temp[0]);
		memcpy(&_magicNumber, temp, 4);

		file.get(temp[3]);
		file.get(temp[2]);
		file.get(temp[1]);
		file.get(temp[0]);
		memcpy(&_items, temp, 4);

		_data = new unsigned char[_items];

		for (int i = 0; i < _items; i++)
		{
			file.get(temp[0]);
			memcpy(_data + i, temp, 1);
		}
	}

	inline unsigned char* GetData() { return _data; }
	inline const int& GetItemCount() const { return _items; }
	inline unsigned char* GetItemData(const unsigned int& filePosition) { return &_data[filePosition]; }
	void FreeData()
	{
		delete[] _data;
		_data = nullptr;
	}

	~LABEL_FILE()
	{
		delete _data;
	}
};