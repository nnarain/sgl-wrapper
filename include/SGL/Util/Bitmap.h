#pragma once

#include <SGL/Util/SGLExport.h>

#include <string>
#include <fstream>
#include <cstdint>

namespace sgl
{
	SGLCLASS Bitmap
	{
	public:
		Bitmap(std::string name);
		~Bitmap();

		bool load();

		char *data() const;
		uint32_t width() const;
		uint32_t height() const;

	private:
		std::string _name;

		char _header[54];
		uint32_t _dataPos;
		uint32_t _width, _height;
		uint32_t _imageSize;

		char* _imageData;

	};

}
