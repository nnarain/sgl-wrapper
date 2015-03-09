
#include "SGL/Util/Image.h"
#include "SGL/Util/Exception.h"

#include <iostream>
#include <fstream>

using namespace sgl;

Image::Image(const std::string &filename, Format format) :
	_format(format),
	_filename(filename),
	_data(NULL)
{
}

void Image::load()
{
	switch (_format)
	{
	case Image::Format::BMP:
		loadBMP();
		break;
	case Image::Format::TGA:
		loadTGA();
		break;
	}
}

void Image::loadBMP()
{
	std::ifstream file(_filename, std::ifstream::binary);
	Image::BitmapHeader header;

	// check if file is valid
	if (file.good())
	{
		// read the file header
		file.read((char *)&header, sizeof(Image::BitmapHeader));

		// verify the header signature
		if (header.signature[0] == 'B' && header.signature[1] == 'M')
		{
			// set the general image data
			_width  = header.width;
			_height = header.height;

			_size = header.imageDataSize;
			if (_size == 0)
				_size = _width * _height * 3; //pixel width * pixel height * RGB

			// get the image data
			_data = new char[header.imageDataSize];

			file.read(_data, header.imageDataSize);

			// check if the read failed
			if (file.fail())
			{
				throw Exception("Failed to read image data from file: " + _filename);
			}

		}
		else
		{
			throw Exception("Bad signature: " + _filename);
		}
	}
	else
	{
		throw Exception("could not open file: " + _filename);
	}
}

void Image::loadTGA()
{
	throw Exception("TGA not supported");
}

Image::Format Image::getFormat()
{
	return _format;
}

unsigned int Image::getWidth() const
{
	return _width;
}

unsigned int Image::getHeight() const
{
	return _height;
}


char *Image::getData() const
{
	return _data;
}

unsigned int Image::size() const
{
	return _size;
}

Image::~Image(void)
{
	if (_data) delete _data;
}
