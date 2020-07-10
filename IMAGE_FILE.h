#pragma once
#include <fstream>

class IMAGE_FILE
{
private:
	int _magicNumber;
	int _items;
	int _imageHeight;
	int _imageWidth;
	unsigned char* _data;

	const char* _filePath;
public:
	IMAGE_FILE(const char* filePath)
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

		file.get(temp[3]);
		file.get(temp[2]);
		file.get(temp[1]);
		file.get(temp[0]);
		memcpy(&_imageHeight, temp, 4);

		file.get(temp[3]);
		file.get(temp[2]);
		file.get(temp[1]);
		file.get(temp[0]);
		memcpy(&_imageWidth, temp, 4);

		_data = new unsigned char[_items * _imageHeight * _imageWidth];

		for (int i = 0; i < _items * _imageHeight * _imageWidth; i++)
		{
			file.get(temp[0]);
			memcpy(_data + i, temp, 1);
		}
	}

	inline unsigned char* GetData() { return _data; }
	inline const int& GetItemCount() const { return _items; }
	inline const int& GetImageHeight() const { return _imageHeight; }
	inline const int& GetImageWidth() const { return _imageWidth; }

	inline int GetSize() const { return _imageHeight * _imageWidth; }
	inline unsigned char* GetImageData(const unsigned int& filePosition) { return &_data[filePosition * GetSize()]; }

	void FreeData()
	{
		//
		delete[] _data;
		_data = nullptr;
	}

	~IMAGE_FILE()
	{
		delete _data;
	}
};