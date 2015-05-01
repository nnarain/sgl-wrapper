
#include "SGL/Util/Image.h"
#include "SGL/Util/Exception.h"

#include <fstream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace sgl;

/* picopng decode prototype*/
extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);

/* Constructors */

Image::Image(const char *filename, Format format) :
	_format(format),
	_data(NULL),
	_width(0),
	_height(0),
	_size(0)
{
	load(filename);
}

Image::Image(const char *filename) : Image(filename, findFormat(getFileExtension(filename)))
{
}

void Image::load(const char *filename)
{
	switch (_format)
	{
	case Image::Format::BMP:
		loadBMP(filename);
		break;
	case Image::Format::TGA:
		loadTGA(filename);
		break;
	case Image::Format::PNG:
		loadPNG(filename);
		break;
	}
}

void Image::loadBMP(const char *filename)
{
	std::ifstream file(filename, std::ifstream::binary);
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
				_size = _width * _height * 3; // pixel width * pixel height * RGB

			// get the image data
			_data = new char[_size];

			file.read(_data, _size);

			// check if the read failed
			if (file.fail())
			{
				throw Exception("Failed to read image data from file");
			}

		}
		else
		{
			throw Exception("Bad signature: ");
		}
	}
	else
	{
		throw Exception("could not open file");
	}
}

void Image::loadTGA(const char *filename)
{
	std::ifstream file(filename, std::ifstream::binary);
	Image::TGAHeader header;

	// check if the file is valid
	if (file.good())
	{
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
			throw Exception("Failed to read file");
		}

	}
	else
	{
		throw Exception("Failed to open file");
	}
}

void Image::loadPNG(const char * filename)
{
	// raw pixel data
	std::vector<unsigned char> pixels;
	// png width
	unsigned long width;
	// png height
	unsigned long height;

	// load png file
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);

	if (!file.good()) throw Exception("could not open file");

	// file size
	std::streamsize size = 0;
	if (file.seekg(0, std::ios::end).good()) size = file.tellg();
	if (file.seekg(0, std::ios::beg).good()) size -= file.tellg();

	if (size <= 0) throw Exception("File is empty : Image::loadPNG()");

	// png file buffer
	unsigned char * pngBuff = new unsigned char[(unsigned int)size];

	// populate buffer
	file.read((char *)pngBuff, size);

	// load png via picoPNG decode function
	int error = decodePNG(pixels, width, height, pngBuff, (size_t)size);

	// buffer no longer needed
	delete[] pngBuff;

	// check for loading errors
	if (error)
		throw Exception("Failed to load PNG");

	// copy the pixel data into the data
	_data = new char[pixels.size()];

	memcpy(_data, &pixels[0], pixels.size() * sizeof(char));

	// set width and height
	_width  = (unsigned int)width;
	_height = (unsigned int)height;
}

std::string Image::getFileExtension(const std::string &filename)
{
	int len = filename.length();
	int i;

	for (i = len-1; i >= 0; i--)
	{
		if (filename[i] == '.')
		{
			return std::string(&filename[i] + 1);
		}
	}

	return std::string("");
}

Image::Format Image::findFormat(const std::string &ext)
{
	Image::Format format;

	if (ext == "tga")
		format = Image::Format::TGA;
	else if (ext == "bmp")
		format = Image::Format::BMP;
	else if (ext == "png")
		format = Image::Format::PNG;
	else
		throw Exception("unsupported format: " + ext);

	return format;
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
