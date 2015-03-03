#include "SGL/Util/Bitmap.h"

using namespace sgl;

Bitmap::Bitmap(std::string name)
{
	_name = name;
}

bool Bitmap::load()
{
	std::ifstream file;
	file.open(_name, std::ios::binary);

	if (file.is_open()){
		file.read(_header, 54);

		if (_header[0] == 'B' || _header[1] == 'M'){
			_dataPos = *(int*)&(_header[0x0A]);
			_imageSize = *(int*)&(_header[0x22]);
			_width = *(int*)&(_header[0x12]);
			_height = *(int*)&(_header[0x16]);

			if (_imageSize == 0) _imageSize = _width * _height * 3;
			if (_dataPos == 0) _dataPos = 54;

			_imageData = new char[_imageSize];

			file.read(_imageData, _imageSize);

			file.close();
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}

	return true;
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
