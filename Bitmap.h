#pragma once

#include <memory>
#include <string>
#include "Bitmap_Header.h"

class Bitmap
{
private:
	Bitmap_Header _header;
	unsigned char* _buffer;
	std::string _filePath;

public:
	Bitmap(const std::string& file_path);
	Bitmap(const std::string& file_path, const unsigned int & ImageWidth, const unsigned int & ImageHeight, const unsigned short int & BPP = 24, const unsigned int & DPI = 72);

	bool CreateImage() const;

	void WriteImage(const unsigned char* const buffer);

	void FreeImageData();

	inline unsigned char* GetImageArray() const { return _buffer + 54; }

	void Read();
	std::shared_ptr<unsigned char> GetImageData() const;

	inline const unsigned int& GetImageWidth() const { return _header._imageWidth; }
	inline const unsigned int& GetImageHeight() const { return _header._imageHeight; }
	
	~Bitmap();

};