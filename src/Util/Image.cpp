
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
			_data = new char[_size];

			file.read(_data, _size);

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
	std::ifstream file(_filename, std::ifstream::binary);
	Image::TGAHeader header;

	// check if the file is valid
	if (file.good())
	{
		std::cout << sizeof(Image::TGAHeader) << std::endl;

		// read the header
		file.read((char *)&header, sizeof(Image::TGAHeader));

		// set the general image data
		_width = header.width;
		_height = header.height;

		_size = _width * _height * 3;

		// get the image data
		_data = new char[_size];

		file.read(_data, _size);

		if (file.fail())
		{
			throw Exception("Failed to read file: " + _filename);
		}

	}
	else
	{
		throw Exception("Failed to open file: " + _filename);
	}
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
