#include "SGL/Util/Bitmap.h"
#include "SGL/Util/Exception.h"

using namespace sgl;

Bitmap::Bitmap(std::string name) :
	_dataPos(0),
	_imageSize(0),
	_width(0),
	_height(0),
	_imageData(NULL)
{
	_name = name;
}

void Bitmap::load()
{
	std::ifstream file(_name, std::ifstream::binary);
	char header[54];

	if (file.good()){
		file.read(header, 54);

		// verify signature
		if (header[0] == 'B' && header[1] == 'M'){
			_dataPos   = *(int*)&(header[0x0A]);
			_imageSize = *(int*)&(header[0x22]);
			_width     = *(int*)&(header[0x12]);
			_height    = *(int*)&(header[0x16]);

			if (_imageSize == 0) _imageSize = _width * _height * 3;
			if (_dataPos == 0) _dataPos = 54;

			_imageData = new char[_imageSize];

			file.read(_imageData, _imageSize);

			// check if the read was unsuccessful
			if (file.fail())
			{
				throw Exception("Failed to read data from " + _name + ", unexcepted data read");
			}

			if (file.bad())
			{
				throw Exception("Failed to read from " + _name + ", bad stream");
			}
		}
		else{
			throw Exception("invalid bitmap signature: " + _name);
		}
	}
	else{
		throw Exception("Could not open file " + _name);
	}

}

char* Bitmap::data() const
{
	return _imageData;
}

uint32_t Bitmap::width() const
{
	return _width;
}

uint32_t Bitmap::height() const
{
	return _height;
}

Bitmap::~Bitmap()
{
	if (!_imageData) delete _imageData;
}
