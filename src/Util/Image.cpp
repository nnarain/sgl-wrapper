
#include "SGL/Util/Image.h"
#include "SGL/Util/Exception.h"

#include <fstream>
#include <algorithm>
#include <vector>
#include <memory>

using namespace sgl;

/* picopng decode prototype*/
extern int decodePNG(std::vector<unsigned char>& out_image, unsigned long& image_width, unsigned long& image_height, const unsigned char* in_png, size_t in_size, bool convert_to_rgba32 = true);


void Image::load(Texture& texture, const char *filename)
{
	Image::Format format = findFormat(getFileExtension(filename));

	switch (format)
	{
	case Image::Format::BMP:
		loadBMP(texture, filename);
		break;
	case Image::Format::TGA:
		loadTGA(texture, filename);
		break;
	case Image::Format::PNG:
		loadPNG(texture, filename);
		break;
	}
}

void Image::loadBMP(Texture& texture, const char *filename)
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

			unsigned int size = header.imageDataSize;
			if (size == 0)
				size = header.width * header.height * 3; // pixel width * pixel height * RGB

			// get the image data
			char *data = new char[size];
			file.read(data, size);

			// check if the read failed
			if (file.fail())
				throw Exception("Failed to read image data from file");

			// set texture data

			texture.setFormat(Texture::Format::BGR);
			texture.setInternalFormat(Texture::InternalFormat::RGB);

			texture.setWidth(header.width);
			texture.setHeight(header.height);
			texture.data(data);

			// free
			delete[] data;
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

void Image::loadTGA(Texture& texture, const char *filename)
{
	std::ifstream file(filename, std::ifstream::binary);
	Image::TGAHeader header;

	// check if the file is valid
	if (file.good())
	{
		// read the header
		file.read((char *)&header, sizeof(Image::TGAHeader));

		unsigned int size = header.width * header.height * 3;

		// get the image data
		char *data = new char[size];
		file.read(data, size);

		if (file.fail())
			throw Exception("Failed to read file");

		// set the texture data
		texture.setFormat(Texture::Format::BGR);
		texture.setInternalFormat(Texture::InternalFormat::RGB);

		texture.setWidth(header.width);
		texture.setHeight(header.height);
		texture.data(data);

		// release data
		delete[] data;
	}
	else
	{
		throw Exception("Failed to open file");
	}
}

void Image::loadPNG(Texture& texture, const char * filename)
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
	char *data = new char[pixels.size()];
	memcpy(data, &pixels[0], pixels.size() * sizeof(char));

	// set texture data
	texture.setInternalFormat(Texture::InternalFormat::RGBA);
	texture.setFormat(Texture::Format::RGBA);

	texture.setWidth((unsigned int)width);
	texture.setHeight((unsigned int)height);
	texture.data(data);

	// release the pixel data
	delete[] data;
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
