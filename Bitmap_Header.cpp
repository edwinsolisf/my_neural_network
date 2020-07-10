#include "Bitmap_Header.h"

Bitmap_Header::Bitmap_Header(const unsigned int & ImageWidth, const unsigned int & ImageHeight, const unsigned short int & BPP, const unsigned int & DPI, const unsigned int& sizeOfFileHeader, const unsigned int& sizeOfInfoHeader)
{
	this->_headerField[0] = 'B';
	this->_headerField[1] = 'M';

	unsigned int rowSize = ((BPP*ImageWidth + 31) / 32) * 4;

	this->_sizeOfFile = sizeOfFileHeader + sizeOfInfoHeader + rowSize * ImageHeight; // FILE_HEADER_SIZE + INFO_HEADER_SIZE + BUFFER_DATA_SIZE
	
	this->_customData1[0] = 'E';
	this->_customData1[1] = 'L';
	this->_customData2[0] = 'S';
	this->_customData2[1] = 'F';

	this->_startAddress = sizeOfFileHeader + sizeOfInfoHeader; // FILE_HEADER_SIZE + INFO_HEADER_SIZE

	this->_sizeOfInfoHeader = sizeOfInfoHeader;

	this->_imageWidth = ImageHeight;
	this->_imageHeight = ImageWidth;

	this->_colorPlanes = 1;

	this->_bitsPerPixel = BPP;

	this->_compressionMethod = 0;

	this->_sizeOfData = rowSize * ImageHeight;

	this->_horizontalResolution = DPI * 393701 / 10000; //From DotsPerInch to PixelsPerMeter
	this->_verticalResolution = DPI * 393701 / 10000; //From DotsPerInch to PixelsPerMeter

	this->_colorPalette = BPP == 24 ? 0 : 256;
	this->_mainColors = 0;

}

Bitmap_Header::~Bitmap_Header()
{
}
