
#ifndef IMAGE_H
#define IMAGE_H

#include <SGL/Util/SGLExport.h>

#include <string>
#include <cstdint>

namespace sgl
{
	/**
		General Image Loader Class

		Loads Uncompressed Bitmaps, TGA
	*/
	SGLCLASS Image
	{
		NO_COPY(Image);

	public:

		/* Types */

		//! Format
		enum class Format
		{
			BMP, TGA
		};

		//! Bitmap Header
		#pragma pack(1)
		struct BitmapHeader
		{
			char signature[2];             // should be 'BM'
			uint32_t size;                 // unreliable
			uint16_t reserved1;            // 0
			uint16_t reserved2;            // 0
			uint32_t dataOffset;           // offset to image data
			uint32_t bitmapHeaderInfoSize; // 40
			uint32_t width;                //
			uint32_t height;               //
			uint16_t numPlanes;            //
			uint16_t bitsPerPixel;         // 24 for RGB
			uint32_t compression;          // compression type - not supported
			uint32_t imageDataSize;        // size of image data
			uint32_t xRes;                 // horizontal image resolution
			uint32_t yRes;                 // vertical image resolution
			uint32_t numColors;            // number of colors
			uint32_t numImportantColors;   // number of important colors
		};

		// TGA Header
		#pragma pack(1)
		struct TGAHeader
		{
			uint8_t  idLen;
			uint8_t  colorMapType;
			uint8_t  imageType;
			uint16_t cmapStart;
			uint16_t cmapLen;
			uint8_t  cmapDepth;
			uint16_t xoffset;
			uint16_t yoffset;
			uint16_t width;
			uint16_t height;
			uint8_t  pixelDepth;
			uint8_t  imageDescriptor;
		};


		/* Constructors */

		Image(const std::string &filename, Format format);
		Image(const std::string &filename);
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

		/**
			Load an uncompressed Bitmap file
		*/
		void loadBMP();

		/**
			Load an uncompressed TGA file
		*/
		void loadTGA();

		/**
			@return the file extension of the given file name
		*/
		std::string getFileExtension(const std::string &filename);

		/**
			@return the Image::Format corresponding to the given extension string
		*/
		Image::Format findFormat(const std::string &ext);

	};
}

#endif
