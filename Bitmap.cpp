#include "Bitmap.h"
#include <iostream>
#include <fstream>

Bitmap::Bitmap(const std::string & file_path)
	:_header(0, 0, 0, 0), _buffer(nullptr), _filePath(file_path)
{
}

Bitmap::Bitmap(const std::string & file_path, const unsigned int & ImageWidth, const unsigned int & ImageHeight, const unsigned short int & BPP, const unsigned int & DPI)
	:_header(ImageWidth, ImageHeight, BPP, DPI ), _buffer(nullptr), _filePath(file_path)
{
	_buffer = new unsigned char[_header._sizeOfFile];

	unsigned char* headerBuffer = (unsigned char*)&_header;
	
	for (int i = 0; i < sizeof(Bitmap_Header); i++)
		_buffer[i] = headerBuffer[i];
}

bool Bitmap::CreateImage() const
{
	std::ofstream file;
	file.open(_filePath, std::ofstream::binary);

	file.write((const char*)_buffer, _header._sizeOfFile);

	if (file.fail())
		file.close();
		std::cout << "Error: Failed creating file \"" << _filePath << "\"" << std::endl;
		return false;

	std::cout << "File \"" << _filePath << "\" created successfully" << std::endl;
	file.close();
	return true;

}

void Bitmap::WriteImage(const unsigned char * buffer)
{
	const unsigned int rowSize = ((_header._bitsPerPixel*_header._imageWidth + 31) / 32) * 4;
	const unsigned int change = rowSize - (_header._bitsPerPixel * _header._imageWidth/ 8);
	for (unsigned int i = 0; i < _header._imageHeight; i++)
	{
		for (unsigned int j = 0; j < rowSize; j++)
		{
			if ((rowSize - j) > change)
				_buffer[i*rowSize + j + _header._startAddress] = buffer[(i*_header._bitsPerPixel*_header._imageWidth / 8) + j];
			else
				_buffer[i*rowSize + j + _header._startAddress] = 0;
		}
	}

	std::cout << "Bits to File \"" << _filePath << "\" have been written successfully" << std::endl;
}

void Bitmap::FreeImageData()
{
	delete[] _buffer;
	_buffer = nullptr;
}

void Bitmap::Read()
{
	std::ifstream file(_filePath, std::ios_base::binary);

	char temp[5];
	
	//HEADER
	file.get(temp, 3);
	memcpy(&_header._headerField, temp, 2);

	file.get(temp, 5);
	memcpy(&_header._sizeOfFile, temp, 4);

	file.get(temp, 3);
	memcpy(&_header._customData1, temp, 2);

	file.get(temp, 3);
	memcpy(&_header._customData2, temp, 2);
	
	file.get(temp, 5);
	memcpy(&_header._startAddress, temp, 4);

	file.get(temp, 5);
	memcpy(&_header._sizeOfInfoHeader, temp, 4);
	
	file.get(temp, 5);
	memcpy(&_header._imageWidth, temp, 4);

	file.get(temp, 5);
	memcpy(&_header._imageHeight, temp, 4);

	file.get(temp, 3);
	memcpy(&_header._colorPlanes, temp, 2);

	file.get(temp, 3);
	memcpy(&_header._bitsPerPixel, temp, 2);

	file.get(temp, 5);
	memcpy(&_header._compressionMethod, temp, 4);

	file.get(temp, 5);
	memcpy(&_header._sizeOfData, temp, 4);

	file.get(temp, 5);
	memcpy(&_header._horizontalResolution, temp, 4);

	file.get(temp, 5);
	memcpy(&_header._verticalResolution, temp, 4);

	file.get(temp, 5);
	memcpy(&_header._colorPalette, temp, 4);

	file.get(temp, 5);
	memcpy(&_header._mainColors, temp, 4);

	//DATA
	_buffer = new unsigned char[_header._sizeOfFile]{0};
	memcpy(_buffer, &_header, _header._startAddress);
	for (unsigned int i = 0; i < _header._sizeOfData; i++)
	{
		file.get(temp[0]);
		memcpy(_buffer+i+_header._startAddress, temp, 1);
	}
}

std::shared_ptr<unsigned char> Bitmap::GetImageData() const
{
	unsigned char* buffer = new unsigned char[_header._imageWidth*_header._imageHeight*_header._bitsPerPixel / 8]{0};
	const unsigned int rowSize = ((_header._bitsPerPixel*_header._imageWidth + 31) / 32) * 4;
	const unsigned int change = rowSize - (_header._bitsPerPixel * _header._imageWidth / 8);

	for (unsigned int i = 0; i < _header._imageHeight; i++)
		for (unsigned int j = 0; j < rowSize; j++)
			if ((rowSize - j) > change)
				buffer[(i*_header._bitsPerPixel*_header._imageWidth / 8) + j] = _buffer[i*rowSize + j + _header._startAddress];

	return std::shared_ptr<unsigned char>(buffer);
}

Bitmap::~Bitmap()
{
	if (_buffer)
		delete[] _buffer;
}
