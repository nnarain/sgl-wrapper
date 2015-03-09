
#ifndef IMAGE_H
#define IMAGE_H

#include <SGL/Util/SGLExport.h>

#include <string>
#include <cstdint>

namespace sgl
{
	SGLCLASS Image
	{
	public:

		/* Types */

		//! Format
		enum class Format
		{
			BMP, TGA
		};

		//! Bitmap Header
		#pragma pack(2)
		struct BitmapHeader
		{
			char signature[2];
			uint32_t size; // unreliable
			uint16_t reserved1; // 0
			uint16_t reserved2; // 0
			uint32_t dataOffset; // offset to image data
			uint32_t bitmapHeaderInfoSize; // 40
			uint32_t width;
			uint32_t height;
			uint16_t numPlanes;
			uint16_t bitsPerPixel;
			uint32_t compression;
			uint32_t imageDataSize;
			uint32_t xRes;
			uint32_t yRes;
			uint32_t numColors;
			uint32_t numImportantColors;
		};


		/* Constructors */

		Image(const std::string &filename, Format format);
		~Image(void);

		/* Public Functions */

		void load();

		/* Getters */

		Format getFormat();

		unsigned int getWidth() const;
		unsigned int getHeight() const;

		char *getData() const;

		unsigned int size() const;

	private:

		Format _format;
		std::string _filename;

		unsigned int _width;
		unsigned int _height;

		char*        _data;

		unsigned int _size;

		/* Private Functions */

		void loadBMP();
		void loadTGA();

	};
}

#endif
