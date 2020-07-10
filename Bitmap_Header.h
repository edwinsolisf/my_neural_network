#pragma once

#pragma pack(push)
#pragma pack(1)
class Bitmap_Header
{
private:
	//FILE HEADER
	char _headerField[2];
	unsigned int _sizeOfFile;
	char _customData1[2];
	char _customData2[2];
	unsigned int _startAddress;

	//INFO HEADER
	unsigned int _sizeOfInfoHeader;
	unsigned int _imageWidth;
	unsigned int _imageHeight;
	unsigned short int _colorPlanes;
	unsigned short int _bitsPerPixel;
	unsigned int _compressionMethod;
	unsigned int _sizeOfData;
	int _horizontalResolution;
	int _verticalResolution;
	unsigned int _colorPalette;
	unsigned int _mainColors;

	Bitmap_Header(const unsigned int& ImageWidth, const unsigned int& ImageHeight, const unsigned short int& BPP, const unsigned int& DPI, const unsigned int& sizeOfFileHeader = 14, const unsigned int& sizeOfInfoHeader = 40);
	~Bitmap_Header();

	friend class Bitmap;
};
#pragma pack(pop)